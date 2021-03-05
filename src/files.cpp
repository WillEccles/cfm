#include "files.h"

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

namespace cfm::files {

void list_files(const fs::path& dir, std::vector<fs::path>& flist) {
  flist.clear();
  for (auto& f : fs::directory_iterator(dir)) {
    flist.push_back(f.path());
  }

  for (auto& p : flist) {
    std::cout << p.filename().string() << '\n';
  }
}

};
