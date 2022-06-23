#include <SFML/Graphics.hpp>

sf::Font font;
sf::Text text("ele goosta", font, 30);
void gameloop(sf::RenderWindow* window) {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
        window->close();
    }
  window->clear();
  window->draw(text);
  window->display();
};

int main() { 
  sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "taporra", sf::Style::Fullscreen);

  if (!font.loadFromFile("assets/fonts/prstart.ttf"))
        return EXIT_FAILURE;
  
  while (window.isOpen()) {
    gameloop(&window);
  }

  return 0;
}