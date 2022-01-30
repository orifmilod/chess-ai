#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>

class WindowInterface {
public:
  WindowInterface() = default;

  virtual void Draw(sf::Drawable &drawable) = 0;
  virtual bool isHovering(sf::Shape &shape) = 0;
};
