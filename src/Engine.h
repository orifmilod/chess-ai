#pragma once
#include "Board.h"
#include "Window.h"

class Engine {
private:
  std::shared_ptr<Window> m_window;
  Board m_board;
  sf::Texture m_texture;
  sf::Sprite m_sprite;

public:
  Engine();
  ~Engine();

  void HandleInput();
  void Update();

  static void start();
  bool IsDone();
};

// Extract code to a DrawEngine and all objects that needs to draw something to
// inheirt IDraw and call the to obj.Draw();
