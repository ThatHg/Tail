#include "KeyBinding.h"

KeyBinding::KeyBinding() {
    _keys = std::vector<std::string>
    { "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Escape",
    "LControl",
    "LShift",
    "LAlt",
    "LSystem",
    "RControl",
    "RShift",
    "RAlt",
    "RSystem",
    "Menu",
    "LBracket",
    "RBracket",
    "SemiColon",
    "Comma",
    "Period",
    "Quote",
    "Slash",
    "BackSlash",
    "Tilde",
    "Equal",
    "Dash",
    "Space",
    "Return",
    "BackSpace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Left",
    "Right",
    "Up",
    "Down",
    "Numpad0",
    "Numpad1",
    "Numpad2",
    "Numpad3",
    "Numpad4",
    "Numpad5",
    "Numpad6",
    "Numpad7",
    "Numpad8",
    "Numpad9",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "Pause" };
    LoadKeyBindings();
}

KeyBinding::~KeyBinding() {
}

void KeyBinding::LoadKeyBindings() {
    Config key_config("key_bindings.lua");
    _binded_keys.insert(std::pair<sf::Keyboard::Key, Key>(StringToKey(key_config.GrabString("UP")), Key::UP));
    _binded_keys.insert(std::pair<sf::Keyboard::Key, Key>(StringToKey(key_config.GrabString("DOWN")), Key::DOWN));
    _binded_keys.insert(std::pair<sf::Keyboard::Key, Key>(StringToKey(key_config.GrabString("LEFT")), Key::LEFT));
    _binded_keys.insert(std::pair<sf::Keyboard::Key, Key>(StringToKey(key_config.GrabString("RIGHT")), Key::RIGHT));
}

const std::map<sf::Keyboard::Key, KeyBinding::Key>& KeyBinding::GetBindings() const {
    return _binded_keys;
}

sf::Keyboard::Key KeyBinding::StringToKey(const std::string& str_key) {
    int size = (int)sf::Keyboard::KeyCount;
    for (int i = 0; i < size; ++i) {
        if (_keys[i] == str_key) {
            return (sf::Keyboard::Key)i;
        }
    }
    return sf::Keyboard::Key::Unknown;
}
