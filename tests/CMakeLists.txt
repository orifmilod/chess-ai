project(chess_tests)

# Gtest fails to find Thread.h when cross-compiling, why?!
# set(CMAKE_THREAD_LIBS_INIT "-lpthread")
# set(CMAKE_HAVE_THREADS_LIBRARY 1)
# set(CMAKE_USE_WIN32_THREADS_INIT 0)
# set(CMAKE_USE_PTHREADS_INIT 1)
# set(THREADS_PREFER_PTHREAD_FLAG ON)

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
