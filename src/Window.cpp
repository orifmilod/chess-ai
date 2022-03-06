#include "Window.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdint>
#include <memory>

constexpr std::uint8_t MAX_FPS = 70;

Window::Window(const std::string &title, const sf::Vector2u &size) {
  setup(title, size);
}
Window::~Window() { destroy(); }

void Window::setup(const std::string &title, const sf::Vector2u &size) {
  m_windowTitle = title;
  m_windowSize = size;
  m_isDone = false;
  m_isFullscreen = false;

  create();
}

void Window::create() {
  m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle,
                  sf::Style::Fullscreen);
  m_window.setFramerateLimit(MAX_FPS);
}

void Window::destroy() { m_window.close(); }

void Window::update() {
  std::unique_ptr<sf::Event> event = getEvents();
  while (event) {
    if (event->type == sf::Event::Closed) {
      m_isDone = true;
    } else if (event != nullptr) {
      m_eventManager.triggerEvent(std::move(event));
    }
  }
}

void Window::toggleFullscreen() {
  m_isFullscreen = !m_isFullscreen;
  destroy();
  create();
}

void Window::beginDraw() { m_window.clear(sf::Color::Black); }

void Window::draw(sf::Drawable &drawable) { m_window.draw(drawable); }

void Window::endDraw() { m_window.display(); }

bool Window::isDone() { return m_isDone; }

bool Window::isFullscreen() { return m_isFullscreen; }

sf::Vector2u Window::getWindowSize() { return m_windowSize; }

bool Window::isHovering(sf::Shape &shape) {
  return shape.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
}

std::unique_ptr<sf::Event> Window::getEvents() {
  sf::Event event;
  if (m_window.pollEvent(event)) {
    return std::make_unique<sf::Event>(event);
  }
  return nullptr;
}
