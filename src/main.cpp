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

#include "files.h"

namespace fs = std::filesystem;

bool interactive = true;

// Signal handler for SIGTERM, SIGINT
void ExitSignal([[maybe_unused]] int _sig) {
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
  if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
    interactive = false;
  }

  signal(SIGTERM, ExitSignal);
  signal(SIGINT, ExitSignal);

  // TODO handle resize
  signal(SIGWINCH, [](int){ printf("SIGWINCH\n"); });

  // TODO handle SIGTSTP and SIGCONT
  signal(SIGTSTP, [](int){ printf("SIGTSTP\n"); });
  signal(SIGCONT, [](int){ printf("SIGCONT\n"); });

  if (argc > 1) {
    std::vector<fs::path> flist;
    cfm::files::list_files(argv[1], flist);
  }

  return 0;
}
