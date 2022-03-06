#include "Engine.h"
#include <iostream>

int main() {
  Engine game;

  while (!game.isDone()) {
    // Game loop.
    game.update();
  }
}
