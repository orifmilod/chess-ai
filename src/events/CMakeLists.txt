add_library(events
  EventManager.h
  EventManager.cpp
)

target_include_directories(events
  PRIVATE
  ${PROJECT_SOURCE_DIR}
)
