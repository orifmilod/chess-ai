#include "Constants.h"
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

    // Forward move - Pawn can move forward if only there is no piece in front
    if (isInRange(m_Position.x, m_Position.y + reverse) &&
        !boardPieces[m_Position.y + reverse][m_Position.x]) {
      addMoveIfLegal(m_Position.x, m_Position.y + reverse, moves, boardPieces,
                     m_isWhite);
    }

    // Double forward move - Pawn can move forward if only there is no piece in
    // front
    if (!m_hasMoved && isInRange(m_Position.x, m_Position.y + reverse * 2) &&
        !boardPieces[m_Position.y + reverse * 2][m_Position.x]) {
      addMoveIfLegal(m_Position.x, m_Position.y + reverse * 2, moves,
                     boardPieces, m_isWhite);
    }

    // Upper left move
    addMoveIfLegal(m_Position.x + reverse, m_Position.y + reverse, moves,
                   boardPieces, m_isWhite, true);

    // top right move
    addMoveIfLegal(m_Position.x - reverse, m_Position.y + reverse, moves,
                   boardPieces, m_isWhite, true);

    // TODO: Remove all the moves which will expose a check
    return moves;
  }

  void setPosition(const Position &position) noexcept override {
    m_Position = position;
    m_hasMoved = true;
  }
};
