#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Bishop : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/bishop_black.png";

public:
  Bishop(float sprite_width, float sprite_height)
      : IPiece(sprite_width, sprite_height) {
    type = Piece::BISHOP;

    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load Bishop image.");
    }
    sprite.setTexture(texture);

    auto texture_rect = sprite.getTextureRect();
    sf::Vector2f sprite_size = {
        static_cast<float>(sprite_width / texture_rect.width),
        static_cast<float>(sprite_height / texture_rect.height)};

    sprite.setScale(sprite_size);
  }

  ~Bishop(){};
  void get_available_moves() const override{};
};
