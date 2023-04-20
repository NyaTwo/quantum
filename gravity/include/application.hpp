// application.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include "network.hpp"

struct message {
	message() : x(0.0f), y(0.0f) {}
	message(float x, float y) : x(x), y(y) {}
	inline bool write(byte_stream_writer& writer) {
		return serialize(writer);
	}
	inline bool read(byte_stream_reader& reader) {
		return serialize(reader);
	}
	template <typename T>
	bool serialize(T& stream) {
		bool success = true;
		success &= stream.serialize(x);
		success &= stream.serialize(y);
		return success;
	}
	float x;
	float y;
};

class application {
public:
   application() = default;

   void run();

private:
   bool enter();
   void exit();
   bool update();
   void render();

private:
   void on_closing();
   void on_mouse_moved(int x, int y);
   void on_key_pressed(sf::Keyboard::Key key);
   void on_key_released(sf::Keyboard::Key key);
   void on_button_pressed(sf::Mouse::Button button);
   void on_button_released(sf::Mouse::Button button);
private:
   sf::RenderWindow m_window;
   sf::Clock        m_clock;
   sf::Time         m_apptime;
   sf::Time         m_deltatime;
   sf::CircleShape	myEntity;
   sf::CircleShape  otherEntity;
   sf::Vector2f		entityPositions[16];
   int				activeEntityCount = 0;
   sf::Vector2f     myEntityPosition;
   float			timer;
private:
   bool             m_running{ true };
   network          m_network;
   udp_socket       m_socket;
   ip_address       m_address;
};
