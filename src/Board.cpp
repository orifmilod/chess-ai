#include "Board.h"
#include "Window.h"
#include "utils/Logger.h"
#include <SFML/System/Clock.hpp>

const float SIZE = 100;

void Board::render(Window &window) {
  sf::RectangleShape rectangle;

  // Default settings for each square
  rectangle.setSize({SIZE, SIZE});

  // Draw the dark squares
  for (float y = 0; y < 8; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? SIZE : 0;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::White);
      window.Draw(rectangle);
    }
  }

  for (float y = 0; y < 8; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : SIZE;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::Blue);
      window.Draw(rectangle);
    }
  }
}
