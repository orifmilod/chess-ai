project(Chess)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(piece)
add_subdirectory(utils)
add_subdirectory(events)

add_executable(${PROJECT_NAME}
  main.cpp
  Window.h
  Window.cpp
  Engine.h
  Engine.cpp
  Board.h
  Board.cpp
  Constants.h
)

target_link_directories(${PROJECT_NAME}
  PRIVATE
  utils
  piece
  events
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

target_include_directories(${PROJECT_NAME} 
  PRIVATE
  .
)

target_link_libraries(${PROJECT_NAME} 
  #external 
  sfml-graphics sfml-window sfml-system 
  #internal
  pieces
  utils
  events
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${CMAKE_CURRENT_SOURCE_DIR}/../assets
                       $<TARGET_FILE_DIR:${PROJECT_NAME}>
                   )
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY ../assets/ DESTINATION bin)
