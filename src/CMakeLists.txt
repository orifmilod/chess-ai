project(Chess)

set(SFML_LIBRARY_DIR "../libs/SFML/build/lib")
set(SFML_INCLUDE_DIR "../libs/SFML/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
  piece/PieceFactory.h
  piece/PieceFactory.cpp
  piece/IPiece.h
  piece/Pawn.cpp
  piece/Bishop.cpp
  piece/King.cpp
  piece/Queen.cpp
  piece/Knight.cpp
  piece/Rook.cpp

  utils/Logger.h
)

target_link_directories(${PROJECT_NAME}
  PRIVATE
  ${SFML_LIBRARY_DIR}
  utils
)

target_include_directories(${PROJECT_NAME} 
  PRIVATE
  ${SFML_INCLUDE_DIR}
  .
)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${CMAKE_CURRENT_SOURCE_DIR}/../assets
                       $<TARGET_FILE_DIR:${PROJECT_NAME}>
                   )
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY ../assets/ DESTINATION bin)
