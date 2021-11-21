#pragma once
#include "utils/Logger.h"
#include <SFML/Window/Event.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>

inline const char *to_string(const sf::Event::EventType &eventType) {
  switch (eventType) {
  case sf::Event::EventType::Closed:
    return "Closed";
  case sf::Event::EventType::KeyPressed:
    return "KeyDown";
  case sf::Event::EventType::KeyReleased:
    return "KeyUp";
  case sf::Event::EventType::MouseButtonPressed:
    return "MButtonDown";
  case sf::Event::EventType::MouseButtonReleased:
    return "MButtonUp";
  case sf::Event::EventType::Resized:
    return "WindowResized";
  case sf::Event::EventType::MouseEntered:
    return "MouseEntered";
  default:
    Logger::warn("Event type is not defined");
    return "";
  }
}

struct Observer {
  std::string name;
  std::function<void(std::unique_ptr<sf::Event>)> callback;

  bool operator==(const Observer &other) { return other.name == name; }

  bool operator==(const std::string &_name) { return _name == name; }
};

static std::map<sf::Event::EventType, std::vector<Observer>> callbacks;

class EventManager {
public:
  EventManager();
  ~EventManager();

  // TODO: consider making the event parameter in callback a unqiue_ptr
  static bool
  addObserver(const std::string &name, sf::Event::EventType eventType,
              std::function<void(std::unique_ptr<sf::Event>)> callback);

  void triggerEvent(std::unique_ptr<sf::Event> event);
  static void removeObserver(const std::string &name);

private:
  bool has_focus;
};
