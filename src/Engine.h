#pragma once
#include "Board.h"
#include "Window.h"

class Engine {
private:
  Window m_window;
  Board m_board;
  sf::Texture m_texture;
  sf::Sprite m_sprite;

public:
  Engine();
  ~Engine();

  void HandleInput();
  void Update();
  void Render();

  static void start();
  Window &GetWindow();
};
