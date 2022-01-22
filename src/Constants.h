#pragma once
#include "piece/IPiece.h"

// Maybe a macro for getting the pat
inline const char *to_string(Piece piece) {
  switch (piece) {
  case Piece::PAWN:
    return "PAWN";
  case Piece::BISHOP:
    return "BISHOP";
  case Piece::KING:
    return "KING";
  case Piece::QUEEN:
    return "QUEEN";
  case Piece::ROOK:
    return "ROOK";
  case Piece::KNIGHT:
    return "KNIGHT";
  default:
    Logger::warn("Piece type is not defined");
    return "";
  }
}

constexpr float PIECE_SIZE = 200.0;
constexpr int BOARD_SIZE = 8;

const sf::Color NORMAL_BLUE(25, 181, 254);
const sf::Color HOVERED_BLUE(52, 152, 219);

const sf::Color NORMAL_WHITE(228, 233, 237);
const sf::Color HOVERED_WHITE(191, 191, 191);
