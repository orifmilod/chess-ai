project(Chess)

set(SFML_LIBRARY_DIR "../libs/SFML/build/lib")
set(SFML_INCLUDE_DIR "../libs/SFML/include")

add_executable(${PROJECT_NAME}
  main.cpp
  Window.h
  Window.cpp
  Engine.h
  Engine.cpp
  Board.h
  Board.cpp
  Constants.h

  #Pieces
  piece/IPiece.h

  #Utils
  utils/Logger.h
)

target_include_directories(${PROJECT_NAME} 
  PRIVATE
  ${SFML_INCLUDE_DIR}
  utils
  piece
)


target_link_directories(${PROJECT_NAME}
  PRIVATE
  ${SFML_LIBRARY_DIR}
)


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
