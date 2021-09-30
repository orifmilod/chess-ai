#include "PieceFactory.h"
#include "IPiece.h"

#include "Bishop.cpp"
#include "King.cpp"
#include "Knight.cpp"
#include "Pawn.cpp"
#include "Queen.cpp"
#include "Rook.cpp"

#include "utils/Logger.h"
#include <memory>

std::shared_ptr<IPiece> PieceFactory::create(Piece piece, float sprite_width,
                                             float sprite_height) {
  switch (piece) {
  case Piece::PAWN:
    return std::make_shared<Pawn>(sprite_width, sprite_height);
  case Piece::BISHOP:
    return std::make_shared<Bishop>(sprite_width, sprite_height);
  case Piece::QUEEN:
    return std::make_shared<Queen>(sprite_width, sprite_height);
  case Piece::KING:
    return std::make_shared<King>(sprite_width, sprite_height);
  case Piece::ROOK:
    return std::make_shared<Rook>(sprite_width, sprite_height);
  case Piece::KNIGHT:
    return std::make_shared<Knight>(sprite_width, sprite_height);
  default:
    Logger::error("Data types is not defined");
    return nullptr;
  }
};
