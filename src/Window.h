#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

class Window {
public:
  Window(const std::string &title, const sf::Vector2u &size);
  ~Window();

  void BeginDraw(); // Clear the window.
  void Draw(sf::Drawable &drawable);
  void EndDraw(); // Display the changes.

  void Update();
  bool IsDone();
  bool IsFullscreen();
  sf::Vector2u GetWindowSize();
  void ToggleFullscreen();
  sf::Vector2i GetMousePossition();

private:
  void Setup(const std::string &title, const sf::Vector2u &size);
  void Destroy();
  void Create();
  sf::RenderWindow m_window;
  sf::Vector2u m_windowSize;
  std::string m_windowTitle;
  bool m_isDone;
  bool m_isFullscreen;
};
