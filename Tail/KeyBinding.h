#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <vector>
#include <map>
#include <SFML\Window\Keyboard.hpp>
#include "Config.h"

class KeyBinding {
public:
    enum Key {
        INVALID_KEY = -1,
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
        KEY_COUNT
    };

    KeyBinding();
    ~KeyBinding();
    void LoadKeyBindings();
    const std::map<sf::Keyboard::Key, Key>& GetBindings() const;
    sf::Keyboard::Key StringToKey(const std::string& str_key);
private:
   std::vector<std::string> _keys;
   std::map<sf::Keyboard::Key, Key> _binded_keys;
};

#endif
