#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class InputBase;

class Player : public Entity {
public:
    Player(InputBase* input);
    ~Player();
    virtual void Update(sf::RenderWindow& window, double delta);
private:
    InputBase* _input;
};

#endif
