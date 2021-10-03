#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <sys/_types/_u_int16_t.h>
#include <sys/types.h>

enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };

struct Position {
  u_int x, y;
};

class IPiece {
protected:
  Piece type;
  Position position;
  bool isWhite;
  float sprite_width, sprite_height;

public:
  sf::Texture texture;
  sf::Sprite sprite;
  IPiece(float _sprite_width, float _sprite_height, bool _isWhite)
      : sprite_width(_sprite_width), sprite_height(_sprite_height),
        isWhite(_isWhite){};

  virtual ~IPiece() = default;

  Position get_position() { return position; }
  Piece get_type() { return type; }
  virtual void get_available_moves() const = 0;
};
