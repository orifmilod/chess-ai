#include "Window.h"
#include "utils/Logger.h"
#include <cstdint>
#include <memory>

constexpr std::uint8_t MAX_FPS = 60;

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
  m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle,
                  sf::Style::Fullscreen);
  m_window.setFramerateLimit(MAX_FPS);
}

void Window::Destroy() { m_window.close(); }

void Window::Update() {
  std::unique_ptr<sf::Event> event = GetEvents();
  while (event) {
    if (event->type == sf::Event::Closed) {
      m_isDone = true;
    } else if (event != nullptr) {
      eventManager.triggerEvent(std::move(event));
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

sf::Vector2i Window::GetMousePossition() {
  return sf::Mouse::getPosition(m_window);
}

std::unique_ptr<sf::Event> Window::GetEvents() {
  sf::Event event;
  if (m_window.pollEvent(event)) {
    return std::make_unique<sf::Event>(event);
  }
  return nullptr;
}
