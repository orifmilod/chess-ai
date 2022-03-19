#pragma once
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum class Piece { ROOK, BISHOP, PAWN, KING, QUEEN, KNIGHT };

struct Position {
  // NOLINTNEXTLINE
  u_int x, y;

  bool operator==(const Position &other) {
    return other.x == this->x && other.y == this->y;
  }
};

class IPiece;
using BoardPieces = std::vector<std::vector<std::shared_ptr<IPiece>>>;

class IPiece {
protected:
  Piece m_type;
  bool m_isWhite;
  float m_sprite_width, m_sprite_height;
  Position m_Position;

  bool isInRange(uint x, uint y) const noexcept {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
  };

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
  void addMoveIfLegal(uint x, uint y, std::vector<Position> &moves,
                      const BoardPieces &boardPieces, bool isWhite,
                      bool opponentPieceMustExist = false) const noexcept {
    if (!isInRange(x, y)) {
      return;
    }

    // This is only special case for pawn
    // if an enemy piece exist in top right/left, then the move is legal
    if (opponentPieceMustExist && boardPieces[y][x] &&
        boardPieces[y][x]->m_isWhite != isWhite) {
      moves.emplace_back(Position{.x = x, .y = y});
    } else if (!opponentPieceMustExist) {
      moves.emplace_back(Position{.x = x, .y = y});
    }
  }

public:
  sf::Texture m_texture;
  sf::Sprite m_sprite;
  IPiece(float spriteWidth, float spriteHeight, bool isWhite, Position position)
      : m_isWhite(isWhite), m_sprite_width(spriteWidth),
        m_sprite_height(spriteHeight), m_Position(position){};

  virtual ~IPiece() = default;

  Position getPosition() noexcept { return m_Position; }

  virtual void setPosition(const Position &position) noexcept {
    m_Position = position;
  }

  Piece getType() noexcept { return m_type; }

  /**
   * @brief Get all the legal moves
   * @param boardPieces board and current pieces on it
   * @return Returns all the legal moves
   */
  virtual std::vector<Position> getAvailableMoves(
      const BoardPieces &boardPieces) = 0;

  /**
   * @brief TODO: implemented pinned logic
   * @param boardPieces
   * @return true if piece is pinned, false otherwise
   */
  bool isPiecePinned(const BoardPieces &boardPieces) const noexcept {
    return false;
  }
};
