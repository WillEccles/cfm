#ifdef __APPLE__
# define _DARWIN_C_SOURCE
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
# define __BSD_VISIBLE 1
#endif

#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <iostream>

#include "files.h"
#include "keys.h"
#include "terminal.h"

namespace fs = std::filesystem;

using namespace cfm;

namespace {

// Signal handler for SIGTERM, SIGINT
void sig_exit([[maybe_unused]] int _sig) {
  exit(EXIT_SUCCESS);
}

void sig_resize([[maybe_unused]] int _sig) {
  if (!terminal::update_size()) {
    exit(EXIT_FAILURE);
  }
}

};

int main(int argc, char** argv) {
  signal(SIGTERM, sig_exit);
  signal(SIGINT, sig_exit);
  signal(SIGWINCH, sig_resize);

  // TODO handle SIGTSTP and SIGCONT
  signal(SIGTSTP, [](int){ printf("SIGTSTP\n"); });
  signal(SIGCONT, [](int){ printf("SIGCONT\n"); });

  keys::Key inkey;

  if (terminal::setup()) {
    std::atexit(terminal::reset);
  } else {
    terminal::reset();
    std::cerr << "terminal setup failed\n";
    exit(1);
  }

  while ((inkey = keys::get())) {
    printf("Key: {%x, %x}\r\n", inkey.base, inkey.mod);
    fflush(stdout);
    if (inkey == 'q' || inkey == keys::Key_Escape) {
      std::exit(0);
    }
  }

#if 0
  if (argc > 1) {
    std::vector<files::listent> flist;
    files::list_files(argv[1], flist);
  }
#endif

  return 0;
}
