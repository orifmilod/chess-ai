#include "Board.h"
#include "Constants.h"
#include "Window.h"
#include "piece/IPiece.h"
#include "piece/PieceFactory.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

constexpr float SIZE = 200;
constexpr int BOARD_SIZE = 8;

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
      // Setting it for your side
      std::shared_ptr<IPiece> piece =
          piece_factory.create(BOARD_PIECES_STRUCTURE[i][j]);

      Logger::info("Setting ", BOARD_SIZE - i - 1, " ", BOARD_SIZE - j - 1, " ",
                   to_string(BOARD_PIECES_STRUCTURE[i][j]));
      m_board_pieces[BOARD_SIZE - i - 1][BOARD_SIZE - j - 1] = piece;
    }
  }
}

bool isHovering(sf::RectangleShape &rectangle, Window &window) {
  return rectangle.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(window.GetMousePossition()));
}

void Board::render_pieces(Window &window) {
  // TODO: Check if the textures has been loaded
  // If the user is white side player
  if (m_playingColor == PieceColor::WHITE) {

    Logger::info("Render the pieces from white side");
  } else {
    Logger::info("Render the pieces from white side");
  }
}

void Board::render_board(Window &window) {
  sf::RectangleShape rectangle;
  rectangle.setSize({SIZE, SIZE});

  // Draw the light squares
  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? SIZE : 0;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::White);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window)) {
        rectangle.setFillColor(sf::Color::Green);
      }

      window.Draw(rectangle);
    }
  }

  for (float y = 0; y < BOARD_SIZE; y++) {
    for (float x = 0; x < 4; x++) {
      float offset = int(y) & 1 ? 0 : SIZE;
      rectangle.setPosition((SIZE * x * 2) + offset, SIZE * y);
      rectangle.setFillColor(sf::Color::Blue);

      // TODO: Change the background of the pieces which you can move
      if (isHovering(rectangle, window)) {
        rectangle.setFillColor(sf::Color::Green);
      }

      window.Draw(rectangle);
    }
  }
}

void Board::render(Window &window) {
  render_board(window);
  render_pieces(window);
}
