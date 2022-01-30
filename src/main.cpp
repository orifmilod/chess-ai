#include "Engine.h"
#include <iostream>

int main() {
  Engine game;

  while (!game.IsDone()) {
    // Game loop.
    game.Update();
  }
}
