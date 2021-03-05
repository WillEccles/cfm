#ifndef _CFM_SRC_FILES_H__
#define _CFM_SRC_FILES_H__

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace cfm::files {

void list_files(const fs::path& dir, std::vector<fs::path>& flist);

};

#endif // _CFM_SRC_FILES_H__
