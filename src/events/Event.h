#include "utils/Logger.h"
#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include <vector>

/*
 * Wrapper around SFML EventType
 */
enum class EventType {
  KeyDown = sf::Event::KeyPressed,
  KeyUp = sf::Event::KeyReleased,
  MButtonDown = sf::Event::MouseButtonPressed,
  MButtonUp = sf::Event::MouseButtonReleased,
  WindowResized = sf::Event::Resized,
  MouseEntered = sf::Event::MouseEntered,
  Closed = sf::Event::Closed,
  Null
};

EventType to_event(const sf::Event::EventType &sf_event) {
  switch (sf_event) {
  case sf::Event::Closed:
    return EventType::Closed;
  case sf::Event::KeyPressed:
    return EventType::KeyDown;
  case sf::Event::KeyReleased:
    return EventType::KeyUp;
  case sf::Event::MouseButtonPressed:
    return EventType::MButtonDown;
  case sf::Event::MouseButtonReleased:
    return EventType::MButtonUp;
  case sf::Event::Resized:
    return EventType::WindowResized;
  case sf::Event::MouseEntered:
    return EventType::MouseEntered;
  default:
    Logger::warn("Event type is not defined");
    return EventType::Null;
  }
}

const char *to_string(const EventType &eventType) {
  switch (eventType) {
  case EventType::Closed:
    return "Closed";
  case EventType::KeyDown:
    return "KeyDown";
  case EventType::KeyUp:
    return "KeyUp";
  case EventType::MButtonDown:
    return "MButtonDown";
  case EventType::MButtonUp:
    return "MButtonUp";
  case EventType::WindowResized:
    return "WindowResized";
  case EventType::MouseEntered:
    return "MouseEntered";
  default:
    Logger::warn("Event type is not defined");
    return "";
  }
}
