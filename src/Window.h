#pragma once
#include "WindowInterface.h"
#include "events/EventManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>

class Window : public WindowInterface {
public:
  Window(const std::string &title, const sf::Vector2u &size);
  ~Window();

  // Clear the window.
  void beginDraw();
  void draw(sf::Drawable &drawable) override;

  // Display the changes.
  void endDraw();

  bool isHovering(sf::Shape &shape) override;

  void update();
  bool isDone();
  bool isFullscreen();
  void toggleFullscreen();
  sf::Vector2u getWindowSize();
  std::unique_ptr<sf::Event> getEvents();

private:
  void setup(const std::string &title, const sf::Vector2u &size);
  void destroy();
  void create();
  sf::RenderWindow m_window;
  sf::Vector2u m_windowSize;
  std::string m_windowTitle;
  bool m_isDone;
  bool m_isFullscreen;

  EventManager m_eventManager;
};
