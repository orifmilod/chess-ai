#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };

struct Position {
  u_int x, y;
};

class IPiece;
using BoardPieces = std::vector<std::vector<std::shared_ptr<IPiece>>>;

class IPiece {
protected:
  Piece type;
  bool isWhite;
  float sprite_width, sprite_height;
  Position mPosition;

  /**
   * @brief Add the position passed as a possible move, if it is legal
   *
   * @param x
   * @param y
   * @param moves - current aggregated possbile moves
   * @param boardPieces - pieces on the board
   * @param piece_must_exist - A piece must exist in the testing move (this is
   * used only for pawns going top-left or top-right)
   */
  void add_move_if_legal(
      uint x, uint y, std::vector<Position> &moves,
      const BoardPieces &boardPieces,
      bool opponent_piece_must_exist = false) const noexcept {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
      return;
    }

    // This is only special case for pawn,  if an enemy piece exist in top
    // right/left, then the move is legal
    if (opponent_piece_must_exist && boardPieces[y][x]) {
      moves.emplace_back(Position{.x = x, .y = y});
    } else if (!opponent_piece_must_exist) {
      moves.emplace_back(Position{.x = x, .y = y});
    }
  }

public:
  sf::Texture texture;
  sf::Sprite sprite;
  IPiece(float _sprite_width, float _sprite_height, bool _isWhite,
         Position position)
      : isWhite(_isWhite), sprite_width(_sprite_width),
        sprite_height(_sprite_height), mPosition(position){};

  virtual ~IPiece() = default;

  Position get_position() noexcept { return mPosition; }

  Piece get_type() noexcept { return type; }

  /**
   * @brief Get all the legal moves
   *
   * @param boardPieces board and current pieces on it
   *
   * @return Returns all the legal moves
   */
  virtual std::vector<Position> get_available_moves(
      const BoardPieces &boardPieces) = 0;

  /**
   * @brief TODO: implemented pinned logic
   *
   * @param boardPieces
   *
   * @return true if piece is pinned, false otherwise
   */
  bool isPiecePinned(const BoardPieces &boardPieces) const noexcept {
    return false;
  }
};
