#ifndef _CFM_SRC_TERMINAL_H__
#define _CFM_SRC_TERMINAL_H__

namespace cfm::terminal {

bool backup() noexcept;
bool setup() noexcept;
void reset() noexcept;

bool update_size() noexcept;

bool is_interactive() noexcept;

int rows() noexcept;
int cols() noexcept;

}; // namespace cfm::terminal

#endif // _CFM_SRC_TERMINAL_H__
