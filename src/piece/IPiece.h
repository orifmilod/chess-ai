#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
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

public:
  sf::Texture texture;
  sf::Sprite sprite;
  IPiece(float sprite_width, float sprite_height){};
  virtual ~IPiece(){};

  Position get_position() { return position; }
  Piece get_type() { return type; }
  virtual void get_available_moves() const = 0;
};
