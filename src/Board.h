#pragma once
#include "WindowInterface.h"
#include "events/EventManager.h"
#include "piece/IPiece.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <unordered_map>

class Board {
private:
  sf::Event m_event;
  bool m_mouseClicked;
  bool m_mouseDraging;
  BoardPieces m_board_pieces;
  bool isWhite;
  std::unordered_map<Piece, sf::Texture> m_piece_textures;
  std::shared_ptr<WindowInterface> m_window;

  void render_pieces();
  void render_board();
  void render_possible_moves();

  void setup_pieces();
  void clickedOnBoard(std::unique_ptr<sf::Event> event);

public:
  Board(std::shared_ptr<WindowInterface> window, bool isWhite);
  void render();
  EventManager eventManager;
};
