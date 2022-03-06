#include "IPiece.h"
#include <memory>

class PieceFactory {
public:
  std::shared_ptr<IPiece> create(Piece piece, float spriteWidth,
                                 float spriteHeight, bool isWhite,
                                 Position position);
};
