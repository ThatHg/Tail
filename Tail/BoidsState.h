#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include "EnemyState.h"

class BoidsState : public EnemyState {
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Enemy& enemy, sf::RenderWindow& window, double delta, const Level& level);
    virtual void Enter(Enemy& enemy);
};

#endif // !BOIDS_STATE_H
