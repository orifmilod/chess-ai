project(chess_tests)

find_package(GTest)
message(STATUS ${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
  EngineTests.cpp
  main.cpp
)

enable_testing()

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  ../src/
)

target_link_libraries(${PROJECT_NAME} 
  gtest
  pthread
)
