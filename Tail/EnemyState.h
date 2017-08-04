#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include <SFML\Graphics.hpp>

class Entity;
class RenderWindow;
class Level;

enum Command {
    INVALID_COMMAND,
    FOLLOW,
    IDLE,
    BOIDS,
    EXIT,
    ENTER,
    COMMAND_COUNT,
};

class EnemyState {
public:
    virtual ~EnemyState() {};
    virtual EnemyState* HandleCommand(Command command) = 0;
    virtual void Update(Entity& enemy, sf::RenderWindow& window, float delta, const Level& level) = 0;
    virtual void Enter(Entity& enemy) = 0;
};

#endif