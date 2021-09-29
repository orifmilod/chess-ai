#include "IPiece.h"
#include "utils/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <string>

class Rook : public IPiece {
  const std::string IMAGE_PATH = "../assets/img/rook_black.png";

public:
  Rook() {
    sf::Texture texture;
    if (!texture.loadFromFile(IMAGE_PATH)) {
      Logger::error("Failed to load Rook image.");
    }
    sprite.setTexture(texture);
  }

  ~Rook(){};

  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
  void get_type() const override{};
  void get_available_moves() const override{};
};
