#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class King : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/king_black.png";

public:
  King() {
    sf::Texture texture;
    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load King image.");
    }
    sprite.setTexture(texture);
  }

  ~King(){};

  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
  void get_type() const override{};
  void get_available_moves() const override{};
};
