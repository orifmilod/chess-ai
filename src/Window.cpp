#include "Window.h"
#include "utils/Logger.h"

Window::Window(const std::string &title, const sf::Vector2u &size) {
  Setup(title, size);
}
Window::~Window() { Destroy(); }

void Window::Setup(const std::string &title, const sf::Vector2u &size) {
  m_windowTitle = title;
  m_windowSize = size;
  m_isDone = false;
  m_isFullscreen = false;

  Create();
}

void Window::Create() {
  auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
  m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}

void Window::Destroy() { m_window.close(); }

void Window::Update() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_isDone = true;
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::F5) {
      ToggleFullscreen();
    }
  }
}

void Window::ToggleFullscreen() {
  m_isFullscreen = !m_isFullscreen;
  Destroy();
  Create();
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::Draw(sf::Drawable &drawable) { m_window.draw(drawable); }
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullscreen() { return m_isFullscreen; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }
