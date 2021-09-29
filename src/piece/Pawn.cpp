#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>


class Pawn : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/pawn_black.png";

public:
  Pawn() {
    sf::Texture texture;
    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load Pawn image.");
    }
    sprite.setTexture(texture);
  }

  ~Pawn(){};

  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
  void get_type() const override{};
  void get_available_moves() const override{};
};
