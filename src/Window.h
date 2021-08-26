#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
  Window();
  Window(const std::string &title, const sf::Vector2u &size);
  ~Window();

  void BeginDraw(); // Clear the window.
  void EndDraw();   // Display the changes.
  void Update();
  bool IsDone();
  bool IsFullscreen();
  sf::Vector2u GetWindowSize();
  void ToggleFullscreen();
  void Draw(sf::Drawable &drawable);

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
