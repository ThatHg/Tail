#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class InputBase;

class Player : public Entity {
public:
    Player(InputBase* input);
    ~Player();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, double delta, const Level& level);
private:
    InputBase* _input;
};

#endif
