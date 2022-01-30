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
  void BeginDraw();
  void Draw(sf::Drawable &drawable) override;

  // Display the changes.
  void EndDraw();

  bool isHovering(sf::Shape &shape) override;

  void Update();
  bool IsDone();
  bool IsFullscreen();
  void ToggleFullscreen();
  sf::Vector2u GetWindowSize();
  std::unique_ptr<sf::Event> GetEvents();

private:
  void Setup(const std::string &title, const sf::Vector2u &size);
  void Destroy();
  void Create();
  sf::RenderWindow m_window;
  sf::Vector2u m_windowSize;
  std::string m_windowTitle;
  bool m_isDone;
  bool m_isFullscreen;

  EventManager eventManager;
};
