#ifndef _CFM_SRC_UTIL_H__
#define _CFM_SRC_UTIL_H__

#include <string>

namespace cfm {

[[noreturn]]
void die() noexcept;

[[noreturn]]
void die(const std::string& msg) noexcept;

[[noreturn]]
void die_perror(const std::string& msg) noexcept;

}; // namespace cfm

#endif // _CFM_SRC_UTIL_H__
