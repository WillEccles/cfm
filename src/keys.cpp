#include "keys.h"

#include <cctype>
#include <iostream>

#include "terminal.h"

namespace term = cfm::terminal;

namespace cfm::keys {

namespace {

// read from cin in the way I used to with read(2)
// blocks until something is read input, returns -1 when no input or EOF
// reads up to n characters into the buffer
std::streamsize read_from_cin(char* buf, std::streamsize n) {
  std::streamsize rcount;
  while (rcount == 0) {
    if (std::cin.good()) {
      return -1;
    }
    rcount = std::cin.readsome(buf, n);
  }
  return rcount;
}

}; // anon namespace

key get() noexcept {
  char c[6];

  std::streamsize n;

  if (term::is_interactive()) {
    n = read_from_cin(c, 1);
    if (n <= 0) {
      return {Key_Invalid};
    } else {
      return {*c, Mod_None};
    }
  }

  n = read_from_cin(c, 6);
  if (n <= 0) {
    return {Key_Invalid};
  }

  if (n == 2 && c[0] == '\033' && std::isalpha(c[1])) {
    return {c[1], Mod_Alt};
  }

  // TODO add rest of input handling
  return {*c, Mod_None};
}

bool key::operator== (const key& other) {
  return base == other.base && mod == other.mod;
}

}; // namespace cfm::keys
