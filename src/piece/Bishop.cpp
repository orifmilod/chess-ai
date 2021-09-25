#include "IPiece.h"

class Bishop : public IPiece {
  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
};
