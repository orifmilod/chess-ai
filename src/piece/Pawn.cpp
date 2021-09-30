#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Pawn : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/pawn_black.png";

public:
  Pawn(float sprite_width, float sprite_height)
      : IPiece(sprite_width, sprite_height) {
    type = Piece::PAWN;

    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load Pawn image.");
    }
    sprite.setTexture(texture);

    auto texture_rect = sprite.getTextureRect();
    sf::Vector2f sprite_size = {
        static_cast<float>(sprite_width / texture_rect.width),
        static_cast<float>(sprite_height / texture_rect.height)};

    sprite.setScale(sprite_size);
  }

  ~Pawn(){};
  void get_available_moves() const override{};
};
