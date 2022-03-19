#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <iostream>
#include <string>

const std::string RED = "\e[0;91m";
const std::string BLUE = "\e[0;96m";
const std::string YELLOW = "\e[0;93m";

class Logger {
private:
  enum class Severity { INFO, WARN, ERROR };

  static void printColored(const char *log, Severity severity) {
    const char *colorCode = nullptr;

    switch (severity) {
    case Severity::INFO:
      colorCode = BLUE.c_str();
      break;
    case Severity::WARN:
      colorCode = YELLOW.c_str();
      break;
    case Severity::ERROR:
      colorCode = RED.c_str();
      break;
    }

    std::cout << "\033" << colorCode << log << "\033[0m ";
  }

  template <class Args> static void printArgs(Args args) {
    std::cout << args << " ";
  }

public:
  template <class... Args> static void info(Args &&...args) {
    printColored("[INFO]", Severity::INFO);
    int dummy[] = {0, ((void)printArgs(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }

  template <class... Args> static void warn(Args &&...args) {
    printColored("[WARN]", Severity::WARN);
    int dummy[] = {0, ((void)printArgs(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }

  template <class... Args> static void error(Args &&...args) {
    printColored("[ERROR]", Severity::ERROR);
    int dummy[] = {0, ((void)printArgs(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }
};
// NOLINTNEXTLINE
#pragma GCC diagnostic pop
