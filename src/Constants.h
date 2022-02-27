#pragma once
#include "piece/IPiece.h"

namespace Constants {
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
constexpr float BOARD_LENGTH = BOARD_SIZE * PIECE_SIZE;

const sf::Color NORMAL_BLUE(25, 181, 254);
const sf::Color HOVERED_BLUE(52, 152, 219);

const sf::Color NORMAL_WHITE(228, 233, 237);
const sf::Color HOVERED_WHITE(191, 191, 191);
const sf::Color MOVE_COLOR(169, 169, 169);

constexpr int MOVE_SIZE = 30;

/**
 * @brief Calculates offset value for an item to be in center of a container
 * (top-left respective)
 *
 * @param container_width
 * @param item_width
 *
 * @return
 */
// int cntr(int container_width, int item_width) {
// return (container_width / 2) - (item_width / 2);
// }

const int MOVE_OFFSET = PIECE_SIZE / 2 - MOVE_SIZE;

/*
 * This structure was designed for black, for white iteration needs to be in
 * reverse order
 */
const std::vector<std::vector<Piece>> BOARD_PIECES_STRUCTURE = {
    {
        Piece::ROOK,
        Piece::KNIGHT,
        Piece::BISHOP,
        Piece::QUEEN,
        Piece::KING,
        Piece::BISHOP,
        Piece::KNIGHT,
        Piece::ROOK,
    },
    {
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
        Piece::PAWN,
    }};

} // namespace Constants
