#include "terminal.h"

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/ioctl.h>

namespace cfm {

terminal::terminal() {
  interactive_ = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
  is_setup_ = false;
  setup();
}

terminal::~terminal() {
  if (interactive_ && is_setup_) {
    reset();
  }
}

void terminal::setup() {
  if (interactive_ && !is_setup_) {
    is_setup_ = true;

    updatesize();
    backup();


    if (setvbuf(stdout, NULL, _IOFBF, 0) != 0) {
      std::perror("terminal::setup: setvbuf");
      // TODO exception
      reset();
      return;
    }

    struct termios new_term = old_term_;
    new_term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    new_term.c_oflag &= ~OPOST;
    new_term.c_cflag |= CS8;
    new_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term) < 0) {
      std::perror("terminal::setup: tcsetattr");
      // TODO exception
      reset();
      return;
    }

    std::printf(
        "\033[?1049h" // alternate screen buffer
        "\033[?7l"    // disable line wrapping
        "\033[?25l"   // hide cursor
        "\033[2J"     // clear screen
        "\033[2;%dr", // limit scroll region
        rows_ - 1);
  }
}

void terminal::reset() {
  if (interactive_ && is_setup_) {
    std::setvbuf(stdout, NULL, _IOLBF, 0);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term_) < 0) {
      std::perror("terminal::reset: tcsetattr");
    }

    std::printf(
        "\033[?7h"  // enable line wrapping
        "\033[?25h" // unhide cursor
        "\033[r"    // reset scroll region
        "\033[?1049l" // restore main screen
        );

    std::fflush(stdout);
  }
}

void terminal::updatesize() {
  if (interactive_) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0) {
      perror("terminal::updatesize: ioctl");
      // TODO exception
      reset();
    }

    rows_ = ws.ws_row;
    cols_ = ws.ws_col;
  }
}

bool terminal::interactive() const noexcept {
  return interactive_;
}

void terminal::backup() {
  if (interactive_) {
    if (tcgetattr(STDIN_FILENO, &old_term_) < 0) {
      // TODO errno thing
    }
  }
}

}; // namespace cfm
