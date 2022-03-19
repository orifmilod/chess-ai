#include "Board.h"
#include "Constants.h"
#include "Window.h"
#include "piece/IPiece.h"
#include "piece/PieceFactory.h"
#include "utils/Logger.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <math.h>
#include <memory>
#include <optional>
#include <vector>

namespace {
/*
 * Checks if the mouse click wan the board and if so return the index of the
 * board cell
 */
std::optional<Position> clickedPiece(sf::Event::MouseButtonEvent mouseEvent) {
  if (mouseEvent.x > Constants::BOARD_LENGTH ||
      mouseEvent.y > Constants::BOARD_LENGTH) {
    return std::nullopt;
  }

  return Position{.x = static_cast<uint>(ceil(mouseEvent.x / 200)),
                  .y = static_cast<uint>(ceil(mouseEvent.y / 200))};
}

} // namespace

Board::Board(std::shared_ptr<WindowInterface> window, bool isWhite)
    : m_isWhite(isWhite), m_window(window) {
  m_mouseClicked = false;
  m_mouseDraging = false;
  setupPieces();

  m_eventManager.addObserver(
      "mouse-click", sf::Event::EventType::MouseButtonPressed,
      std::bind(&Board::clickedOnBoard, this, std::placeholders::_1));
}

// TODO: Use uint for iteration and  need for static_cast
void Board::setupPieces() {
  PieceFactory pieceFactory;
  m_board_pieces.resize(
      Constants::BOARD_SIZE,
      std::vector<std::shared_ptr<IPiece>>(Constants::BOARD_SIZE, nullptr));

  // Add white pieces to the board
  for (int i = 0; i < Constants::BOARD_PIECES_STRUCTURE.size(); i++) {
    for (int j = Constants::BOARD_PIECES_STRUCTURE[0].size() - 1; j >= 0; j--) {
      std::shared_ptr<IPiece> piece = pieceFactory.create(
          Constants::BOARD_PIECES_STRUCTURE[i][Constants::BOARD_SIZE - j - 1],
          Constants::PIECE_SIZE, Constants::PIECE_SIZE, true,
          {.x = static_cast<uint>(Constants::BOARD_SIZE - j - 1),
           .y = static_cast<uint>(Constants::BOARD_SIZE - i - 1)});

      m_board_pieces[Constants::BOARD_SIZE - i - 1]
                    [Constants::BOARD_SIZE - j - 1] = piece;
    }
  }

  // Add black pieces to the board
  for (int i = Constants::BOARD_PIECES_STRUCTURE.size() - 1; i >= 0; i--) {
    for (int j = Constants::BOARD_PIECES_STRUCTURE[0].size() - 1; j >= 0; j--) {
      std::shared_ptr<IPiece> piece = pieceFactory.create(
          Constants::BOARD_PIECES_STRUCTURE[i][j], Constants::PIECE_SIZE,
          Constants::PIECE_SIZE, false,
          {.x = static_cast<uint>(j), .y = static_cast<uint>(i)});

      m_board_pieces[i][j] = piece;
    }
  }
}

void Board::renderPieces() {
  for (int row = 0; row < Constants::BOARD_SIZE; row++) {
    for (int col = 0; col < Constants::BOARD_SIZE; col++) {
      if (m_board_pieces[row][col]) {
        m_board_pieces[row][col]->m_sprite.setPosition(
            col * Constants::PIECE_SIZE, row * Constants::PIECE_SIZE);
        m_window->draw(m_board_pieces[row][col]->m_sprite);
      }
    }
  }
}

void Board::renderBoard() {
  sf::RectangleShape rectangle;
  rectangle.setSize({Constants::PIECE_SIZE, Constants::PIECE_SIZE});

  // Draw the light squares
  for (float y = 0; y < Constants::BOARD_SIZE; y++) {
    for (float x = 0; x < Constants::BOARD_SIZE / 2.0; x++) {
      float offset = int(y) & 1 ? Constants::PIECE_SIZE : 0;
      rectangle.setPosition((Constants::PIECE_SIZE * x * 2) + offset,
                            Constants::PIECE_SIZE * y);
      rectangle.setFillColor(Constants::NORMAL_WHITE);

      // Change the background of the pieces which you can move
      if (m_window->isHovering(rectangle) && m_board_pieces[y][x]) {
        rectangle.setFillColor(Constants::HOVERED_WHITE);
      }

      m_window->draw(rectangle);
    }
  }

  // Draw the dark squares
  for (float y = 0; y < Constants::BOARD_SIZE; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : Constants::PIECE_SIZE;
      rectangle.setPosition((Constants::PIECE_SIZE * x * 2) + offset,
                            Constants::PIECE_SIZE * y);
      rectangle.setFillColor(Constants::NORMAL_BLUE);

      // Change the background of the pieces which can be moved
      // i.e can't move pieces which are pinned
      if (m_window->isHovering(rectangle) && m_board_pieces[y][x]) {
        rectangle.setFillColor(Constants::HOVERED_BLUE);
      }

      m_window->draw(rectangle);
    }
  }
}

void Board::renderPossibleMoves() {
  sf::CircleShape moveShape;
  moveShape.setRadius(Constants::MOVE_SIZE);
  moveShape.setFillColor(Constants::MOVE_COLOR);

  for (int i = 0; i < m_possibleMoves.m_moves.size(); i++) {
    moveShape.setPosition(Constants::PIECE_SIZE * m_possibleMoves.m_moves[i].x +
                              Constants::MOVE_OFFSET,
                          Constants::PIECE_SIZE * m_possibleMoves.m_moves[i].y +
                              Constants::MOVE_OFFSET);
    m_window->draw(moveShape);
  }
}

void Board::render() {
  renderBoard();
  renderPieces();
  renderPossibleMoves();
}

void Board::clickedOnBoard(std::unique_ptr<sf::Event> event) {
  // Check if the mouse clicked on any of the pieces
  std::optional<Position> maybePiecePosition = clickedPiece(event->mouseButton);
  // Did not click on the board or any piece on the board
  if (!maybePiecePosition.has_value()) {
    m_possibleMoves.m_moves.clear();
    Logger::info("Did not click on the board");
    return;
  }

  // Check if clicked on the moves
  auto it =
      std::find(m_possibleMoves.m_moves.begin(), m_possibleMoves.m_moves.end(),
                maybePiecePosition.value());
  if (it != m_possibleMoves.m_moves.end()) {
    Logger::info("Made a move to ", it->x, it->y);
    movePiece(Move{.m_from = m_possibleMoves.m_currentPosition, .m_to = *it});
    m_possibleMoves.m_moves.clear();
    return;
  }

  if (!m_board_pieces[maybePiecePosition->y][maybePiecePosition->x]) {
    m_possibleMoves.m_moves.clear();
    Logger::info("Didn't click on any piece");
    return;
  }

  std::vector<Position> possibleMoves =
      m_board_pieces[maybePiecePosition->y][maybePiecePosition->x]
          ->getAvailableMoves(m_board_pieces);

  m_possibleMoves =
      PossibleMoves{.m_currentPosition = maybePiecePosition.value(),
                    .m_moves = std::move(possibleMoves)};
}

void Board::movePiece(Move move) {
  Logger::info("From:", move.m_from.x, move.m_from.y, ", To:", move.m_to.x,
               move.m_to.y);

  // Move piece from start to end position
  m_board_pieces[move.m_to.y][move.m_to.x] =
      std::move(m_board_pieces[move.m_from.y][move.m_from.x]);

  // Set the position of the piece
  m_board_pieces[move.m_to.y][move.m_to.x]->setPosition(move.m_to);

  // Set start pos to nullptr
  m_board_pieces[move.m_from.y][move.m_from.x] = nullptr;
}
