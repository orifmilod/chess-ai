#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>


class Bishop : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/bishop_black.png";

public:
  Bishop() {
    sf::Texture texture;
    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load Bishop image.");
    }
    sprite.setTexture(texture);
  }

  ~Bishop(){};

  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
  void get_type() const override{};
  void get_available_moves() const override{};
};
