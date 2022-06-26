#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "SFMLMath.hpp"

#define WIDTH 400
#define HEIGHT 400

sf::Vector2f offset(WIDTH/2, HEIGHT/2);

// hehe
sf::Font font;
sf::Text text("que isso meu fi calma", font, 15);

bool clicking;
bool dragging;

sf::Vector2f last_mouse_position;

sf::Vector2f init_mouse_position(0, 0);
sf::Vector2f end_mouse_position(0, 0);

float getDirection(float num) {
	int calc = std::round(num/90); 
	return calc % 4;
}

void gameloop(sf::RenderWindow *window) {
  sf::Event event;

	sf::Vector2f actual_mouse_position = sf::Vector2f(sf::Mouse::getPosition(*window));
	
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window->close();
  }

  sf::RectangleShape rect(sf::Vector2f(400, 400));
  rect.setFillColor(sf::Color::Green);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (!clicking) {
      init_mouse_position = actual_mouse_position - offset;
    }
    clicking = true;
    // text.setString("TOME");

  } else {
    if (clicking) {
      end_mouse_position = actual_mouse_position - offset;
    }
		if (dragging)
    clicking = false;
    // text.setString("CAVALO");
  }


	sf::Vector2f distance = init_mouse_position - end_mouse_position;
  dragging = actual_mouse_position != last_mouse_position && clicking; 
	// && sf::getLength(distance) > 40;
	
  if (dragging) {
    rect.setFillColor(sf::Color(20,20,20));
	  
		float angle = sf::getRotationAngle(distance);
		int direction = getDirection(angle);
		
		text.setString(std::to_string(direction));
		
  } else {
		rect.setFillColor(sf::Color::Black);
	  std::string init_string =
	      std::to_string(init_mouse_position.x) + ", " +
	      std::to_string(init_mouse_position.y);
		std::string end_string =
				std::to_string(end_mouse_position.x) + ", " +
				std::to_string(end_mouse_position.y);
  	text.setString(init_string + "\n" + end_string);
	}
  
  window->clear();
  window->draw(rect);
  window->draw(text);
  window->display();
};

int main() {
  sf::RenderWindow window(sf::VideoMode(400, 400), "taporra");

  window.setVerticalSyncEnabled(false);
	
  if (!font.loadFromFile("assets/fonts/prstart.ttf"))
    return EXIT_FAILURE;

  while (window.isOpen()) {
    gameloop(&window);
    sf::sleep(sf::milliseconds(16));
  }

  return 0;
}