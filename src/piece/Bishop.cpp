#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Bishop : public IPiece {
  const std::string BLACK_IMAGE_PATH = "../assets/img/bishop_black.png";
  const std::string WHITE_IMAGE_PATH = "../assets/img/bishop_white.png";

public:
  Bishop(float spriteWidth, float spriteHeight, bool isWhite, Position position)
      : IPiece(spriteWidth, spriteHeight, isWhite, position) {
    m_type = Piece::BISHOP;

    if (!m_texture.loadFromFile(isWhite ? WHITE_IMAGE_PATH
                                        : BLACK_IMAGE_PATH)) {
      Logger::error("Failed to load Bishop image.");
    }
    m_sprite.setTexture(m_texture);

    auto textureRect = m_sprite.getTextureRect();
    sf::Vector2f spriteSize = {
        static_cast<float>(spriteWidth / textureRect.width),
        static_cast<float>(spriteHeight / textureRect.height)};

    m_sprite.setScale(spriteSize);
  }

  ~Bishop(){};

  std::vector<Position> getAvailableMoves(
      const BoardPieces &boardPieces) override {
    return {};
  };
};
