#include "Board.h"
#include "Constants.h"
#include "Window.h"
#include "piece/IPiece.h"
#include "piece/PieceFactory.h"
#include "utils/Logger.h"
#include <SFML/Graphics.hpp>
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
  if (mouseEvent.x > BOARD_LENGTH || mouseEvent.y > BOARD_LENGTH) {
    return std::nullopt;
  }

  return Position{.x = static_cast<uint>(ceil(mouseEvent.x / 200)),
                  .y = static_cast<uint>(ceil(mouseEvent.y / 200))};
}

} // namespace

Board::Board(std::shared_ptr<WindowInterface> window, bool _isWhite)
    : m_window(window), isWhite(_isWhite) {
  m_mouseClicked = false;
  m_mouseDraging = false;
  setup_pieces();

  eventManager.addObserver(
      "mouse-click", sf::Event::EventType::MouseButtonPressed,
      std::bind(&Board::clickedOnBoard, this, std::placeholders::_1));
}

void Board::setup_pieces() {
  PieceFactory piece_factory;
  m_board_pieces.resize(
      BOARD_SIZE, std::vector<std::shared_ptr<IPiece>>(BOARD_SIZE, nullptr));

  // Add the pieces to the board for white
  for (int i = 0; i < BOARD_PIECES_STRUCTURE.size(); i++) {
    for (int j = BOARD_PIECES_STRUCTURE[0].size() - 1; j >= 0; j--) {
      std::shared_ptr<IPiece> piece =
          piece_factory.create(BOARD_PIECES_STRUCTURE[i][BOARD_SIZE - j - 1],
                               PIECE_SIZE, PIECE_SIZE, true);

      m_board_pieces[BOARD_SIZE - i - 1][BOARD_SIZE - j - 1] = piece;
    }
  }

  for (int i = BOARD_PIECES_STRUCTURE.size() - 1; i >= 0; i--) {
    for (int j = BOARD_PIECES_STRUCTURE[0].size() - 1; j >= 0; j--) {
      std::shared_ptr<IPiece> piece = piece_factory.create(
          BOARD_PIECES_STRUCTURE[i][j], PIECE_SIZE, PIECE_SIZE, false);

      m_board_pieces[i][j] = piece;
    }
  }
}

void Board::render_pieces() {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      if (m_board_pieces[row][col]) {
        m_board_pieces[row][col]->sprite.setPosition(col * PIECE_SIZE,
                                                     row * PIECE_SIZE);
        m_window->Draw(m_board_pieces[row][col]->sprite);
      }
    }
  }
}

void Board::render_board() {
  sf::RectangleShape rectangle;
  rectangle.setSize({PIECE_SIZE, PIECE_SIZE});

  // Draw the light squares
  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < BOARD_SIZE / 2.0; x++) {
      float offset = int(y) & 1 ? PIECE_SIZE : 0;
      rectangle.setPosition((PIECE_SIZE * x * 2) + offset, PIECE_SIZE * y);
      rectangle.setFillColor(NORMAL_WHITE);

      // Change the background of the pieces which you can move
      if (m_window->isHovering(rectangle) && m_board_pieces[y][x]) {
        rectangle.setFillColor(HOVERED_WHITE);
      }

      m_window->Draw(rectangle);
    }
  }

  // Draw the dark squares
  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : PIECE_SIZE;
      rectangle.setPosition((PIECE_SIZE * x * 2) + offset, PIECE_SIZE * y);
      rectangle.setFillColor(NORMAL_BLUE);

      // Change the background of the pieces which can be moved
      // i.e can't move pieces which are pinned
      if (m_window->isHovering(rectangle) && m_board_pieces[y][x]) {
        rectangle.setFillColor(HOVERED_BLUE);
      }

      m_window->Draw(rectangle);
    }
  }
}

void Board::render() {
  render_board();
  render_pieces();
}

void Board::clickedOnBoard(std::unique_ptr<sf::Event> event) {
  // Check if the mouse clicked on any of the pieces
  std::optional<Position> maybePiecePosition = clickedPiece(event->mouseButton);
  // Did not click on the board or any piece on the board
  if (!maybePiecePosition.has_value() ||
      !m_board_pieces[maybePiecePosition->y][maybePiecePosition->x]) {
    Logger::info("Did not click on any piece");
    return;
  }

  Logger::info("Clicked on a piece at x:", maybePiecePosition.value().x,
               ", y: ", maybePiecePosition.value().y);
}
