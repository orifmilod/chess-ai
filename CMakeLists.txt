cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(tests)

file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/*.h)

add_custom_target(
  clang-format
  COMMAND clang-format
  -style=file
  -i
  ${ALL_SOURCE_FILES}
)


