#include "IPiece.h"

// Maybe a macro for getting the pat
inline const char *get_image_path(Piece piece) {
  switch (piece) {
  case Piece::BISHOP:
    return "../assets/img/Chess_blt60.png";
  case Piece::PAWN:
    return "../assets/img/Chess_bdt60.png";
  case Piece::ROOK:
    return "../assets/img/Chess_bdt60.png";
  };
}
