#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "InputBase.h"
#include "KeyBinding.h"

class PlayerInput : public InputBase {
public:
    PlayerInput();
    virtual void Update(Entity& entity, double delta);
private:
    KeyBinding _key_bindings;
};

#endif