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

  std::vector<Position> get_available_moves(
      const BoardPieces &boardPieces) override {
    int reverse = isWhite ? -1 : 1;

    std::vector<Position> moves;
    if (!hasMoved) {
      moves.emplace_back(
          Position{.x = mPosition.x, .y = mPosition.y + reverse * 2});
    }

    // Forward move
    add_move_if_legal(mPosition.x, mPosition.y + reverse * 1, moves,
                      boardPieces);

    // Upper left move
    add_move_if_legal(mPosition.x + reverse * 1, mPosition.y + reverse * 1,
                      moves, boardPieces, true);

    // top right move
    add_move_if_legal(mPosition.x - reverse * 1, mPosition.y + reverse * 1,
                      moves, boardPieces, true);

    // TODO: Remove all the moves which will expose a check

    return moves;
  }
};
