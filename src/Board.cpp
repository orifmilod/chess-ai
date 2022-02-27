#include "Board.h"
#include "Constants.h"
#include "Window.h"
#include "piece/IPiece.h"
#include "piece/PieceFactory.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System.hpp>
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

Board::Board(std::shared_ptr<WindowInterface> window, bool _isWhite)
    : isWhite(_isWhite), m_window(window) {
  m_mouseClicked = false;
  m_mouseDraging = false;
  setup_pieces();

  eventManager.addObserver(
      "mouse-click", sf::Event::EventType::MouseButtonPressed,
      std::bind(&Board::clickedOnBoard, this, std::placeholders::_1));
}

// TODO: Use uint for iteration and  need for static_cast
void Board::setup_pieces() {
  PieceFactory piece_factory;
  m_board_pieces.resize(
      Constants::BOARD_SIZE,
      std::vector<std::shared_ptr<IPiece>>(Constants::BOARD_SIZE, nullptr));

  // Add white pieces to the board
  for (int i = 0; i < Constants::BOARD_PIECES_STRUCTURE.size(); i++) {
    for (int j = Constants::BOARD_PIECES_STRUCTURE[0].size() - 1; j >= 0; j--) {
      std::shared_ptr<IPiece> piece = piece_factory.create(
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
      std::shared_ptr<IPiece> piece = piece_factory.create(
          Constants::BOARD_PIECES_STRUCTURE[i][j], Constants::PIECE_SIZE,
          Constants::PIECE_SIZE, false,
          {.x = static_cast<uint>(j), .y = static_cast<uint>(i)});

      m_board_pieces[i][j] = piece;
    }
  }
}

void Board::render_pieces() {
  for (int row = 0; row < Constants::BOARD_SIZE; row++) {
    for (int col = 0; col < Constants::BOARD_SIZE; col++) {
      if (m_board_pieces[row][col]) {
        m_board_pieces[row][col]->sprite.setPosition(
            col * Constants::PIECE_SIZE, row * Constants::PIECE_SIZE);
        m_window->Draw(m_board_pieces[row][col]->sprite);
      }
    }
  }
}

void Board::render_board() {
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

      m_window->Draw(rectangle);
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

      m_window->Draw(rectangle);
    }
  }
}

void Board::render_possible_moves() {
  sf::CircleShape moveShape;
  moveShape.setRadius(Constants::MOVE_SIZE);
  moveShape.setFillColor(Constants::MOVE_COLOR);

  for (int i = 0; i < m_possibleMoves.size(); i++) {
    moveShape.setPosition(
        Constants::PIECE_SIZE * m_possibleMoves[i].x + Constants::MOVE_OFFSET,
        Constants::PIECE_SIZE * m_possibleMoves[i].y + Constants::MOVE_OFFSET);
    m_window->Draw(moveShape);
  }
}

void Board::render() {
  render_board();
  render_pieces();
  render_possible_moves();
}

void Board::clickedOnBoard(std::unique_ptr<sf::Event> event) {
  // Check if the mouse clicked on any of the pieces
  std::optional<Position> maybePiecePosition = clickedPiece(event->mouseButton);
  // Did not click on the board or any piece on the board
  if (!maybePiecePosition.has_value() ||
      !m_board_pieces[maybePiecePosition->y][maybePiecePosition->x]) {
    m_possibleMoves.clear();
    Logger::info("Did not click on any piece");
    return;
  }

  std::vector<Position> possibleMoves =
      m_board_pieces[maybePiecePosition->y][maybePiecePosition->x]
          ->get_available_moves(m_board_pieces);

  m_possibleMoves = std::move(possibleMoves);

  for (const Position &move : possibleMoves) {
    Logger::info("x:", move.x, "y", move.y);
  }
}

void Board::movePiece(Move move) {
  // Move piece from start to end position
  m_board_pieces[move.endPosition.y][move.endPosition.x] =
      std::move(m_board_pieces[move.startPosition.y][move.startPosition.x]);

  // Set start pos to nullptr
  m_board_pieces[move.startPosition.y][move.startPosition.x] = nullptr;
}
