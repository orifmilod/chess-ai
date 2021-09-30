#include "IPiece.h"
#include <memory>

class PieceFactory {
public:
  std::shared_ptr<IPiece> create(Piece piece, float sprite_width,
                                 float sprite_height);
};
