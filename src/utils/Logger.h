#pragma once
#include <iostream>
#include <string>

const std::string RED = "\e[0;91m";
const std::string BLUE = "\e[0;96m";
const std::string YELLOW = "\e[0;93m";

class Logger {
private:
  enum class Severity { INFO, WARN, ERROR };

  static void print_colored(const char *log, Severity severity) {
    const char *color_code = nullptr;

    switch (severity) {
    case Severity::INFO:
      color_code = BLUE.c_str();
      break;
    case Severity::WARN:
      color_code = YELLOW.c_str();
      break;
    case Severity::ERROR:
      color_code = RED.c_str();
      break;
    }

    std::cout << "\033" << color_code << log << "\033[0m -- ";
  }

  template <class Args> static void print_args(Args args) {
    std::cout << args << " ";
  }

public:
  template <class... Args> static void info(Args &&...args) {
    print_colored("[INFO] ", Severity::INFO);
    int dummy[] = {0, ((void)print_args(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }

  template <class... Args> static void warn(Args &&...args) {
    print_colored("[WARN] ", Severity::WARN);
    int dummy[] = {0, ((void)print_args(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }

  template <class... Args> static void error(Args &&...args) {
    print_colored("[ERROR]", Severity::ERROR);
    int dummy[] = {0, ((void)print_args(std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
  }
};
