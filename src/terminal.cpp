#include "terminal.h"

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "util.h"

namespace cfm::terminal {

namespace {
bool interactive_ = false;
struct termios old_term_;
int rows_;
int cols_;
};

bool setup() noexcept {
  interactive_ = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);

  if (interactive_) {
    if (!update_size()) {
      return false;
    }

    if (!backup()) {
      return false;
    }

    if (setvbuf(stdout, NULL, _IOFBF, 0) != 0) {
      std::perror("terminal::setup: setvbuf");
      return false;
    }

    struct termios new_term = old_term_;
    new_term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    new_term.c_oflag &= ~OPOST;
    new_term.c_cflag |= CS8;
    new_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) < 0) {
      std::perror("terminal::setup: tcsetattr");
      return false;
    }

    std::printf(
        "\033[?1049h" // alternate screen buffer
        "\033[?7l"    // disable line wrapping
        "\033[?25l"   // hide cursor
        "\033[2J"     // clear screen
        "\033[2;%dr", // limit scroll region
        rows_ - 1);

    std::fflush(stdout);
  }

  return true;
}

void reset() noexcept {
  if (interactive_) {
    std::setvbuf(stdout, NULL, _IOLBF, 0);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term_) < 0) {
      std::perror("terminal::reset: tcsetattr");
    }

    std::printf(
        "\033[?7h"    // enable line wrapping
        "\033[?25h"   // unhide cursor
        "\033[r"      // reset scroll region
        "\033[?1049l" // restore main screen
        );

    std::fflush(stdout);
  }
}

bool update_size() noexcept {
  if (interactive_) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0) {
      std::perror("terminal::updatesize: ioctl");
      return false;
    }

    rows_ = ws.ws_row;
    cols_ = ws.ws_col;
  }

  return true;
}

bool is_interactive() noexcept {
  return interactive_;
}

bool backup() noexcept {
  if (interactive_) {
    if (tcgetattr(STDIN_FILENO, &old_term_) < 0) {
      std::perror("terminal::backup: tcgetattr");
      return false;
    }
  }

  return true;
}

int rows() noexcept {
  return rows_;
}

int cols() noexcept {
  return cols_;
}

}; // namespace cfm
