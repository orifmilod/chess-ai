#include "Constants.h"
#include "Engine.h"
#include "Window.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Vector2.hpp>

Engine::Engine()
    : m_window(std::make_shared<Window>("Chess AI", sf::Vector2u(1200, 900))),
      m_board(m_window, true) {
  Logger::info("Engine created");
}

Engine::~Engine() { Logger::info("Engine has been destroyed"); }

void Engine::start() { Logger::info("Starting the engine"); };

void Engine::update() {
  m_window->update();

  m_window->beginDraw();
  m_board.render();
  m_window->endDraw();
}

bool Engine::isDone() { return m_window->isDone(); }
