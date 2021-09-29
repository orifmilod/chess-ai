#pragma once
#include "piece/IPiece.h"

// Maybe a macro for getting the pat
inline const char *get_image_path(Piece piece) {
  switch (piece) {
  case Piece::BISHOP:
    return "../assets/img/Chess_blt60.png";
  case Piece::PAWN:
    return "../assets/img/Chess_bdt60.png";
  case Piece::ROOK:
    return "../assets/img/Chess_bdt60.png";
  case Piece::KING:
    return "../assets/img/Chess_bdt60.png";
  case Piece::KNIGHT:
    return "../assets/img/Chess_bdt60.png";
  case Piece::QUEEN:
    return "../assets/img/Chess_bdt60.png";
  };
}

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
