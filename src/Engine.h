#include "Window.h"

class Engine {
private:
  Window m_window;
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
