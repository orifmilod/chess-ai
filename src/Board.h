#pragma once
#include "Window.h"
#include <SFML/Window/Event.hpp>

class Board {
private:
  sf::Event m_event;
  bool m_mouseClicked;
  bool m_mouseDraging;

public:
  Board();
  void render(Window &window);
  void hover();
};
