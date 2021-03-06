#ifndef _CFM_SRC_KEYS_H__
#define _CFM_SRC_KEYS_H__

#include <optional>

namespace cfm::keys {

enum key_mods {
  none,
  shift,
  ctrl,
  alt,
};

// special key values
enum special_keys : int {
  Key_Invalid = -1,

  Key_Up = 0x100,
  Key_Down,
  Key_Left,
  Key_Right,
  Key_Pageup,
  Key_Pagedown,
  Key_Escape,
};

struct key {
  int base;
  key_mods mod;

  bool operator== (const key& other);
};

key get() noexcept;

}; // namespace cfm::input

#endif // _CFM_SRC_KEYS_H__
