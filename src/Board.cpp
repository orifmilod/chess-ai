#include "Board.h"
#include "Constants.h"
#include "Window.h"
#include "piece/IPiece.h"
#include "piece/PieceFactory.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

constexpr float PIECE_SIZE = 200.0;
constexpr int BOARD_SIZE = 8;

const sf::Color NORMAL_BLUE(25, 181, 254);
const sf::Color HOVERED_BLUE(52, 152, 219);

const sf::Color NORMAL_WHITE(228, 233, 237);
const sf::Color HOVERED_WHITE(191, 191, 191);

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

Board::Board(PieceColor color) : m_playingColor(color) {
  m_mouseClicked = false;
  m_mouseDraging = false;
  setup_pieces();
}

void Board::setup_pieces() {
  PieceFactory piece_factory;
  m_board_pieces.resize(
      BOARD_SIZE, std::vector<std::shared_ptr<IPiece>>(BOARD_SIZE, nullptr));

  // Add the pieces to the board
  for (int i = 0; i < BOARD_PIECES_STRUCTURE.size(); i++) {
    for (int j = 0; j < BOARD_PIECES_STRUCTURE[i].size(); j++) {
      std::shared_ptr<IPiece> piece = piece_factory.create(
          BOARD_PIECES_STRUCTURE[i][j], PIECE_SIZE, PIECE_SIZE);

      m_board_pieces[BOARD_SIZE - i - 1][BOARD_SIZE - j - 1] = piece;
    }
  }
}

bool isHovering(sf::RectangleShape &rectangle, Window &window) {
  return rectangle.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(window.GetMousePossition()));
}

void Board::render_pieces(Window &window) {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      if (m_board_pieces[row][col]) {
        m_board_pieces[row][col]->sprite.setPosition(col * PIECE_SIZE,
                                                     row * PIECE_SIZE);
        window.Draw(m_board_pieces[row][col]->sprite);
      }
    }
  }
}

void Board::render_board(Window &window) {
  sf::RectangleShape rectangle;
  rectangle.setSize({PIECE_SIZE, PIECE_SIZE});

  // Draw the light squares
  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < BOARD_SIZE / 2.0; x++) {
      float offset = int(y) & 1 ? PIECE_SIZE : 0;
      rectangle.setPosition((PIECE_SIZE * x * 2) + offset, PIECE_SIZE * y);
      rectangle.setFillColor(NORMAL_WHITE);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window) && m_board_pieces[y][x]) {
        rectangle.setFillColor(HOVERED_WHITE);
      }

      window.Draw(rectangle);
    }
  }

  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : PIECE_SIZE;
      rectangle.setPosition((PIECE_SIZE * x * 2) + offset, PIECE_SIZE * y);
      rectangle.setFillColor(NORMAL_BLUE);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window) && m_board_pieces[y][x]) {
        rectangle.setFillColor(HOVERED_BLUE);
      }

      window.Draw(rectangle);
    }
  }
}

void Board::render(Window &window) {
  render_board(window);
  render_pieces(window);
}
