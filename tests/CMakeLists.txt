project(chess_tests)

set(GTEST_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/libs/gtest/build/lib")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/gtest/googletest/include")

add_executable(${PROJECT_NAME}
  EngineTests.cpp
  main.cpp
)

enable_testing()

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  ../src/
  ${GTEST_INCLUDE_DIR}
)

target_link_directories(${PROJECT_NAME}
  PRIVATE
  ${GTEST_LIBRARY_DIR}
)
target_link_libraries(${PROJECT_NAME} 
  gtest
)

