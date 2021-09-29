#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <sys/types.h>

enum class PieceColor { BLACK, WHITE };
enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };


struct Position {
  u_int x, y;
};

class IPiece {
protected:
  Piece type;
  Position position;
  PieceColor color;
  sf::Sprite sprite;

public:
  virtual ~IPiece(){};

  virtual void get_position() const = 0;
  virtual void get_type() const = 0;
  virtual void get_available_moves() const = 0;
};
