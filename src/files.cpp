#include "files.h"

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

namespace cfm::files {

listent::listent(const fs::directory_entry& _dirent):
    dirent(_dirent)
{}

void list_files(const fs::path& dir, std::vector<listent>& flist) {
  flist.clear();
  for (auto& f : fs::directory_iterator(dir)) {
    flist.push_back(listent(f));
  }

  for (auto& p : flist) {
    std::cout << p.dirent.path().filename().string() << '\n';
  }
}

};
