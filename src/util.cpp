#include "util.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "terminal.h"

namespace cfm {

[[noreturn]]
void die() noexcept {
  if (terminal::is_interactive()) {
    terminal::reset();
  }

  exit(1);
}

[[noreturn]]
void die(const std::string& msg) noexcept {
  if (terminal::is_interactive()) {
    terminal::reset();
  }

  std::cerr << msg << '\n';

  exit(1);
}

[[noreturn]]
void die_perror(const std::string& msg) noexcept {
  if (terminal::is_interactive()) {
    terminal::reset();
  }

  std::perror(msg.c_str());

  exit(1);
}

}; // namespace cfm
