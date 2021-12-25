project(chess_tests)

find_package(GTest REQUIRED)

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
  pthread
  GTest::GTest
)
