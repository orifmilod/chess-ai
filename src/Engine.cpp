#include "Engine.h"
#include "Constants.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Vector2.hpp>

Engine::Engine()
    : m_window("Chess AI", sf::Vector2u(1200, 900)), m_board(true) {
  Logger::info("Engine created");
}
Engine::~Engine() { Logger::info("Engine is being destroyed"); }

void Engine::start() { Logger::info("Starting the engine"); };

void Engine::Update() { m_window.Update(); }

void Engine::Render() {
  m_window.BeginDraw();
  m_board.render(m_window);
  m_window.EndDraw();
}

Window &Engine::GetWindow() { return m_window; }
void Engine::HandleInput() {}
