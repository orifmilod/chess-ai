#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Pawn : public IPiece {
  bool m_hasMoved = false;
  const std::string BLACK_IMAGE_PATH = "../assets/img/pawn_black.png";
  const std::string WHITE_IMAGE_PATH = "../assets/img/pawn_white.png";

public:
  Pawn(float spriteWidth, float spriteHeight, bool isWhite, Position position)
      : IPiece(spriteWidth, spriteHeight, isWhite, position) {
    m_type = Piece::PAWN;

    if (!m_texture.loadFromFile(isWhite ? WHITE_IMAGE_PATH
                                        : BLACK_IMAGE_PATH)) {
      Logger::error("Failed to load Pawn image.");
    }
    m_sprite.setTexture(m_texture);

    auto textureRect = m_sprite.getTextureRect();
    sf::Vector2f spriteSize = {
        static_cast<float>(spriteWidth / textureRect.width),
        static_cast<float>(spriteHeight / textureRect.height)};

    m_sprite.setScale(spriteSize);
  }

  ~Pawn(){};

  std::vector<Position> getAvailableMoves(
      const BoardPieces &boardPieces) override {
    int reverse = m_isWhite ? -1 : 1;

    std::vector<Position> moves;
    if (!m_hasMoved) {
      moves.emplace_back(
          Position{.x = m_Position.x, .y = m_Position.y + reverse * 2});
    }

    // Forward move
    addMoveIfLegal(m_Position.x, m_Position.y + reverse * 1, moves,
                   boardPieces);

    // Upper left move
    addMoveIfLegal(m_Position.x + reverse * 1, m_Position.y + reverse * 1,
                   moves, boardPieces, true);

    // top right move
    addMoveIfLegal(m_Position.x - reverse * 1, m_Position.y + reverse * 1,
                   moves, boardPieces, true);

    // TODO: Remove all the moves which will expose a check

    return moves;
  }
};
