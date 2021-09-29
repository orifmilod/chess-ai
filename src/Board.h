#pragma once
#include "Window.h"
#include "piece/IPiece.h"
#include <SFML/Window/Event.hpp>
#include <memory>
#include <unordered_map>

class Board {

private:
  sf::Event m_event;
  bool m_mouseClicked;
  bool m_mouseDraging;
  std::vector<std::vector<std::shared_ptr<IPiece>>> m_board_pieces;
  PieceColor m_playingColor;
  std::unordered_map<Piece, sf::Texture> m_piece_textures;
  void render_board(Window &window);
  void render_pieces(Window &window);
  void setup_pieces();

public:
  Board(PieceColor color);
  void render(Window &window);
};
