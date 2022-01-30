#include "Engine.h"
#include "Constants.h"
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

void Engine::Update() {
  m_window->Update();

  m_window->BeginDraw();
  m_board.render();
  m_window->EndDraw();
}

bool Engine::IsDone() { return m_window->IsDone(); }
