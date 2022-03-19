#pragma once
#include "WindowInterface.h"
#include "events/EventManager.h"
#include "piece/IPiece.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace {
struct Move {
  Position m_from;
  Position m_to;
};

struct PossibleMoves {
  Position m_currentPosition;
  std::vector<Position> m_moves;
};

} // namespace

class Board {
private:
  sf::Event m_event;
  bool m_mouseClicked;
  bool m_mouseDraging;
  BoardPieces m_board_pieces;
  bool m_isWhite;
  std::unordered_map<Piece, sf::Texture> m_piece_textures;
  std::shared_ptr<WindowInterface> m_window;

  void renderPieces();
  void renderBoard();
  void renderPossibleMoves();

  void setupPieces();
  void clickedOnBoard(std::unique_ptr<sf::Event> event);
  void movePiece(Move move);
  EventManager m_eventManager;
  PossibleMoves m_possibleMoves;

public:
  Board(std::shared_ptr<WindowInterface> window, bool isWhite);
  void render();
};
