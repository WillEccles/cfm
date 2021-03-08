#ifndef _CFM_SRC_FILES_H__
#define _CFM_SRC_FILES_H__

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace cfm::files {

struct listent {
  fs::directory_entry dirent;
  bool marked = false;

  listent(const fs::directory_entry& _dirent);
};

void list_files(const fs::path& dir, std::vector<listent>& flist);

};

#endif // _CFM_SRC_FILES_H__
