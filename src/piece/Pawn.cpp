#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Pawn : public IPiece {
  bool hasMoved = false;
  const std::string BLACK_IMAGE_PATH = "../assets/img/pawn_black.png";
  const std::string WHITE_IMAGE_PATH = "../assets/img/pawn_white.png";

public:
  Pawn(float sprite_width, float sprite_height, bool isWhite, Position position)
      : IPiece(sprite_width, sprite_height, isWhite, position) {
    type = Piece::PAWN;

    if (!texture.loadFromFile(isWhite ? WHITE_IMAGE_PATH : BLACK_IMAGE_PATH)) {
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

  std::vector<Position>
  get_available_moves(const BoardPieces &boardPieces) override {
    if (isPiecePinned(boardPieces)) {
      return {};
    }
    std::vector<Position> moves;

    if (!hasMoved) {
      moves.emplace_back(Position{.x = mPosition.x + 2, .y = mPosition.y});
      hasMoved = true;
    }

    return moves;
  }
};
