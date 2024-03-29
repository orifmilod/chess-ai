cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CUSTOM_FLAGS "-Wall")

if(NOT "${FSANITIZE}" STREQUAL "")
  string(APPEND CUSTOM_FLAGS " -fsanitize=${FSANITIZE}")
endif()

message(STATUS "Compile with CXX_FLAGS set: ${CUSTOM_FLAGS}")
set(CMAKE_CXX_FLAGS ${CUSTOM_FLAGS})

# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_SYSTEM_PROCESSOR arm)
# 
# set(PATH "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin")
# 
# set(triple arm-linux-gnueabihf)
# set(CMAKE_C_COMPILER "${PATH}/clang")
# set(CMAKE_C_COMPILER_TARGET ${triple})
# set(CMAKE_CXX_COMPILER "${PATH}/clang++")
# set(CMAKE_CXX_COMPILER_TARGET ${triple})


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

add_custom_target(
  tidy
  COMMAND clang-tidy
  -p ${PROJECT_SOURCE_DIR}/build
  --fix
  ${ALL_SOURCE_FILES}
)


