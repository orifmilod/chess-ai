#include "src/Engine.h"
#include <iostream>

int main() {
  Engine game;

  while (!game.GetWindow().IsDone()) {
    // Game loop.
    game.HandleInput();
    game.Update();
    game.Render();
  }
}
