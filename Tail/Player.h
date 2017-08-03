#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class InputBase;
class PhysicsComponent;
class GraphicsComponent;

class Player : public Entity {
public:
    Player();
    ~Player();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level);
};

#endif
