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
    n = read_from_cin(buf, 1);
    if (n <= 0) {
      return -1;
    } else {
      return *c;
    }
  }

  n = read_from_cin(buf, 6);
  if (n <= 0) {
    return -1;
  }

  if (n == 2 && c[0] == '\033' && std::isalpha(c[1])) {
    return K_ALT(c[1]);
  }
}

bool key::operator== (const key& other) {
  return base == other.base && mod == other.mod;
}

}; // namespace cfm::keys