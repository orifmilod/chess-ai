#pragma once
#include <sys/types.h>

enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };

struct Position {
  u_int x, y;
};

class IPiece {
protected:
  Piece type;
  Position position;

public:
  virtual void get_position() const;
  virtual void get_type() const;
};
