add_library(pieces 
  PieceFactory.h
  PieceFactory.cpp
  IPiece.h
  Pawn.cpp
  Bishop.cpp
  King.cpp
  Queen.cpp
  Knight.cpp
  Rook.cpp
)

target_include_directories(pieces 
  PRIVATE
  ${PROJECT_SOURCE_DIR}
)
