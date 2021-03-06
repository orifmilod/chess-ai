#include "EventManager.h"
#include "utils/Logger.h"
#include <algorithm>
#include <vector>

/*
 * Todo: add explanation
 */
EventManager::EventManager() = default;
EventManager::~EventManager() {
  Logger::info("Unsubscribing all the callback");
  callbacks.clear();
}

bool EventManager::addObserver(
    const std::string &name, sf::Event::EventType eventType,
    std::function<void(std::unique_ptr<sf::Event>)> callback) {
  // const std::vector<Observer> &observers = callbacks[eventType];

  // bool observer_exist = std::find(observers.begin(), observers.end(),
  // callback) != observers.end();
  // if (observer_exist) {
  // Logger::warn("Callback with the same name and event type already exist",
  // to_string(eventType), callback);
  // return false;
  // }

  callbacks[eventType].emplace_back(
      Observer{.m_name = name, .m_callback = std::move(callback)});
  Logger::info("Observer:", name, "subscribed to:", toString(eventType));
  return true;
}

void EventManager::removeObserver(const std::string &name) {
  bool foundObserver = false;

  for (const auto &[eventType, observers] : callbacks) {
    for (const Observer &observer : observers) {
      if (observer.m_name == name) {
        Logger::info("Observer has removed, observer name:", name,
                     "event type:", toString(eventType));
        break;
        foundObserver = true;
      }
    }

    if (foundObserver) {
      break;
    }
  }

  if (!foundObserver) {
    Logger::warn("No such event type has been registered before");
  }
}

void EventManager::triggerEvent(std::unique_ptr<sf::Event> event) {
  for (const auto &observer : callbacks[event->type]) {
    observer.m_callback(std::move(event));
  }
}
