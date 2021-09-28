#pragma once
#include "Window.h"
#include "piece/IPiece.h"
#include <SFML/Window/Event.hpp>

enum class PlayingColor { BLACK, WHITE };
class Board {

private:
  sf::Event m_event;
  bool m_mouseClicked;
  bool m_mouseDraging;
  std::vector<std::vector<IPiece>> board_pieces;
  PlayingColor playingColor;

public:
  Board(PlayingColor color);
  void render(Window &window);
  void hover();
  void reset_board_pieces();
};
