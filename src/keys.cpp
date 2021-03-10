#include "keys.h"

#include <cctype>
#include <iostream>
#include <unistd.h>
#include <cstdio>

#include "terminal.h"

namespace term = cfm::terminal;

namespace cfm::keys {

namespace {
const char ESC_UP = 'A';
const char ESC_DOWN = 'B';
const char ESC_LEFT = 'D';
const char ESC_RIGHT = 'C';
}; // anon namespace

Key get() noexcept {
  char c[6];

  std::streamsize n;

  if (term::is_interactive()) {
    n = read(STDIN_FILENO, c, 1);
    if (n <= 0) {
      return {Key_Invalid, Mod_None};
    } else {
      return {*c, Mod_None};
    }
  }

  n = read(STDIN_FILENO, c, 6);
  if (n <= 0) {
    return {Key_Invalid, Mod_None};
  }

  if (n == 2 && c[0] == '\033' && std::isalpha(c[1])) {
    return {c[1], Mod_Alt};
  }

  if (n < 3) {
    std::printf("n < 3: c[0] = %d\r\n", c[0]);
    return {c[0], Mod_None};
  }

  if (n == 3) {
    switch (c[2]) {
      case ESC_UP:
        return {Key_Up, Mod_None};
      case ESC_DOWN:
        return {Key_Down, Mod_None};
      case ESC_RIGHT:
        return {Key_Right, Mod_None};
      case ESC_LEFT:
        return {Key_Left, Mod_None};
    }
  } else if (n == 4) {
    if (c[3] == '~') {
      switch (c[2]) {
        case '5':
          return {Key_PageUp, Mod_None};
        case '6':
          return {Key_PageDown, Mod_None};
      }
    }
  } else if (n == 6) {
    if (c[2] == '1' && c[3] == ';' && c[4] == '2') {
      switch (c[5]) {
        case 'A':
          return {Key_PageUp, Mod_None};
        case 'B':
          return {Key_PageDown, Mod_None};
      }
    }
  }

  return {Key_Invalid, Mod_None};
}

bool Key::operator== (const Key& other) const noexcept {
  return base == other.base && mod == other.mod;
}

bool Key::operator!= (const Key& other) const noexcept {
  return !(*this == other);
}

bool Key::operator== (int val) const noexcept {
  return base == val;
}

bool Key::operator!= (int val) const noexcept {
  return base != val;
}

Key::operator bool () const noexcept {
  return base != Key_Invalid;
}

}; // namespace cfm::keys
