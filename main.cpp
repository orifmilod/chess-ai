#include "Constants.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

void load_chess_pieces() {
  sf::Texture texture;
  if (!texture.loadFromFile(get_image_path(Piece::BISHOP),
                            sf::IntRect(10, 10, 62, 62))) {
    Logger::error("Could not load image");
  }
  Logger::info("Loaded the image");
}

int main() {
  sf::Window window(sf::VideoMode(800, 600), "Chess AI");
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();
      }
      load_chess_pieces();
  }
  return 0;
}
