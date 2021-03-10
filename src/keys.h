#ifndef _CFM_SRC_KEYS_H__
#define _CFM_SRC_KEYS_H__

#include <optional>

namespace cfm::keys {

enum key_mods : int {
  Mod_None,
  Mod_Ctrl,
  Mod_Alt,
};

// special key values
enum special_keys : int {
  Key_Invalid = -1,

  Key_Up = 0x100,
  Key_Down,
  Key_Left,
  Key_Right,
  Key_PageUp,
  Key_PageDown,
  Key_Home,
  Key_End,

  Key_Escape = '\033',
};

struct Key {
  int base;
  key_mods mod;

  bool operator== (const Key& other) const noexcept;
  bool operator!= (const Key& other) const noexcept;

  bool operator== (int val) const noexcept;
  bool operator!= (int val) const noexcept;

  operator bool () const noexcept;
};

Key get() noexcept;

}; // namespace cfm::keys

#endif // _CFM_SRC_KEYS_H__
