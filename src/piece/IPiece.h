#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };

struct Position {
  u_int x, y;
};

class IPiece;
using BoardPieces = std::vector<std::vector<std::shared_ptr<IPiece>>>;

class IPiece {
protected:
  Piece type;
  Position position;
  bool isWhite;
  float sprite_width, sprite_height;
  Position mPosition;

public:
  sf::Texture texture;
  sf::Sprite sprite;
  IPiece(float _sprite_width, float _sprite_height, bool _isWhite,
         Position position)
      : sprite_width(_sprite_width), sprite_height(_sprite_height),
        isWhite(_isWhite), mPosition(position){};

  virtual ~IPiece() = default;

  Position get_position() noexcept { return position; }

  Piece get_type() noexcept { return type; }

  /*
   * Return all the position move positions for the current piece
   */
  virtual std::vector<Position>
  get_available_moves(const BoardPieces &boardPieces) = 0;

  /*
   * TODO: implemented pinned logic
   */
  bool isPiecePinned(const BoardPieces &boardPieces) const noexcept {
    return false;
  }
};
