#ifndef _CFM_SRC_TERMINAL_H__
#define _CFM_SRC_TERMINAL_H__

#include <termios.h>

namespace cfm {

class terminal {
public:
  terminal();
  ~terminal();

  void setup();
  void reset();

  void updatesize();

  bool interactive() const noexcept;

private:
  bool is_setup_;
  bool interactive_;
  struct termios old_term_;
  int rows_;
  int cols_;

  void backup();
};

}; // namespace cfm::terminal

#endif // _CFM_SRC_TERMINAL_H__
