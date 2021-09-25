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

bool isRectClicked(sf::RectangleShape &shape) {
  sf::IntRect rect(shape.getPosition().x, shape.getPosition().y,
                   shape.getLocalBounds().width, shape.getLocalBounds().height);

  if (rect.contains(sf::Mouse::getPosition()) &&
      (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
    return true;
  }
  return false;
}

void Board::render(Window &window) {
  Logger::error(sf::Mouse::getPosition().x, " ", sf::Mouse::getPosition().y);
  sf::RectangleShape rectangle;
  Logger::info(sf::Mouse::getPosition().x, " ", sf::Mouse::getPosition().y);

  // Default settings for each square
  rectangle.setSize({SIZE, SIZE});

  // Draw the light squares
  for (float y = 0; y < 8; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? SIZE : 0;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::White);
      window.Draw(rectangle);
      if (isRectClicked(rectangle)) {
        Logger::warn("y: ", y, "x: ", x, " clicked");
      }
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
