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

std::shared_ptr<IPiece> PieceFactory::create(Piece piece) {
  switch (piece) {
  case Piece::PAWN:
    return std::make_shared<Pawn>();
  case Piece::BISHOP:
    return std::make_shared<Bishop>();
  case Piece::QUEEN:
    return std::make_shared<Queen>();
  case Piece::KING:
    return std::make_shared<King>();
  case Piece::ROOK:
    return std::make_shared<Rook>();
  case Piece::KNIGHT:
    return std::make_shared<Knight>();
  default:
    Logger::error("Data types is not defined");
    return nullptr;
  }
};
