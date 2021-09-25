#include "Board.h"
#include "Window.h"
#include "utils/Logger.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Mouse.hpp>

const float SIZE = 200;

Board::Board() {
  m_mouseClicked = false;
  m_mouseDraging = false;
}

void Board::hover() {
  if (m_event.type == sf::Event::MouseButtonPressed &&
      m_event.mouseButton.button == sf::Mouse::Left) {
    m_mouseClicked = true;
  }
}

bool isHovering(sf::RectangleShape &rectangle, Window &window) {
  return rectangle.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(window.GetMousePossition()));
}

void Board::render(Window &window) {
  sf::RectangleShape rectangle;

  // Default settings for each square
  rectangle.setSize({SIZE, SIZE});

  // Draw the light squares
  for (float y = 0; y < 8; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? SIZE : 0;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::White);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window)) {
        rectangle.setFillColor(sf::Color::Green);
      }

      window.Draw(rectangle);
    }
  }

  for (float y = 0; y < 8; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : SIZE;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::Blue);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window)) {
        rectangle.setFillColor(sf::Color::Green);
      }

      window.Draw(rectangle);
    }
  }
}
