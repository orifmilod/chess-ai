#include "Engine.h"
#include "Constants.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Vector2.hpp>

Engine::Engine() : m_window("Chess AI", sf::Vector2u(1200, 900)) {
  // TODO: Load the sprites into the memory
  if (!m_texture.loadFromFile(get_image_path(Piece::BISHOP),
                              sf::IntRect(10, 10, 62, 62))) {
    Logger::error("Could not load image");
  }
  m_sprite.setTexture(m_texture);

  Logger::info("Engine created");
}
void Engine::start() { Logger::info("Starting the engine"); };

Engine::~Engine() { Logger::info("Engine is being destroyed"); }

void Engine::HandleInput() {

}
void Engine::Update() { m_window.Update(); }

void Engine::Render() {
  m_window.BeginDraw();
  board.render(m_window);
  m_window.EndDraw();
}

Window &Engine::GetWindow() { return m_window; }
