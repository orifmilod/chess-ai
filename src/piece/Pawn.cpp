#include "IPiece.h"
#include "utils/Logger.h"

class Pawn : public IPiece {
  void get_position() const override {
    Logger::info("Getting Bishop position", position.x, position.y);
  }
};
