#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class King : public IPiece {
  const std::string BLACK_IMAGE_PATH = "../assets/img/king_black.png";
  const std::string WHITE_IMAGE_PATH = "../assets/img/king_white.png";

public:
  King(float sprite_width, float sprite_height, bool isWhite, Position position)
      : IPiece(sprite_width, sprite_height, isWhite, position) {
    type = Piece::KING;

    if (!texture.loadFromFile(isWhite ? WHITE_IMAGE_PATH : BLACK_IMAGE_PATH)) {
      Logger::error("Failed to load King image.");
    }
    sprite.setTexture(texture);

    auto texture_rect = sprite.getTextureRect();
    sf::Vector2f sprite_size = {
        static_cast<float>(sprite_width / texture_rect.width),
        static_cast<float>(sprite_height / texture_rect.height)};

    sprite.setScale(sprite_size);
  }

  ~King(){};

  std::vector<Position>
  get_available_moves(const BoardPieces &boardPieces) override {
    return {};
  };
};
