#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include "Component.h"
#include "../KeyBinding.h"

class PlayerInputComponent : public Component {
public:
    PlayerInputComponent();
    ~PlayerInputComponent();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, double delta, const Level& level);
private:
    KeyBinding m_key_bindings;
};

#endif // !PLAYER_INPUT_COMPONENT_H

