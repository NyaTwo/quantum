// application.cpp

#include "application.hpp"

bool application::enter()
{  
    myEntity.setRadius(10);
    myEntity.setPosition(sf::Vector2f(1920 / 3, 1080 / 3));
    myEntity.setFillColor(sf::Color::Magenta);
    otherEntity.setRadius(5);
    otherEntity.setFillColor(sf::Color::Black);
    m_address = ip_address(192, 168, 0, 100, 54321);
    m_socket.open({});
    return true;
}

void application::exit()
{
}

bool application::update()
{
   m_deltatime = m_clock.restart();
   m_apptime += m_deltatime;
   timer += m_deltatime.asSeconds();
   byte_stream stream;
   if (timer > 0.15) {
       myEntityPosition = myEntity.getPosition();
       byte_stream_writer writer(stream);
       message msg;
       msg.x = myEntityPosition.x;
       msg.y = myEntityPosition.y;
       if (msg.write(writer)) {
           if (m_socket.send(m_address, stream)) {
               timer = 0;
           }
       }
   }
   
   if (m_socket.receive(m_address, stream)) {
       activeEntityCount = 0;
       byte_stream_reader reader(stream);
       message msg;
       while (reader.has_data()) {
           if (msg.read(reader)) {
               entityPositions[activeEntityCount] = sf::Vector2f(msg.x, msg.y);
               activeEntityCount++;
           }   
       }
   }

   return m_running;
}

void application::render()
{
   m_window.clear(sf::Color{ 0x55,0x55,0x55,0xff });
   m_window.draw(myEntity);
   for (int i = 0; i < activeEntityCount; i++) {
       otherEntity.setPosition(entityPositions[i]);
       m_window.draw(otherEntity);
   }
   m_window.display();
}

void application::on_closing()
{
    m_running = false;
}

void application::on_mouse_moved(int x, int y)
{
    myEntity.setPosition(float(x), float(y));
}

void application::on_key_pressed(sf::Keyboard::Key key)
{
   if (key == sf::Keyboard::Key::Escape) {
      m_running = false;
   }
}

void application::on_key_released(sf::Keyboard::Key key)
{
}

void application::on_button_pressed(sf::Mouse::Button button)
{
}

void application::on_button_released(sf::Mouse::Button button)
{
}
