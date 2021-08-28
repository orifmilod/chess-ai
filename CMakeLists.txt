cmake_minimum_required(VERSION 3.0)
project(Chess)
set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "libs/SFML/include")
set(SFML_LIBRARY_DIR "libs/SFML/build/lib")

add_executable(${PROJECT_NAME} 
  main.cpp
  src/Window.h
  src/Window.cpp
  src/Engine.h
  src/Engine.cpp
  src/Board.h
  src/Board.cpp

  #Utils
  src/utils/Logger.h
)

target_include_directories(${PROJECT_NAME}
  PRIVATE 
  ${SFML_INCLUDE_DIR}
  src
  utils
)

target_link_directories(${PROJECT_NAME} 
  PRIVATE ${SFML_LIBRARY_DIR}
)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
