#ifndef FOLLOWING_STATE_H
#define FOLLOWING_STATE_H

#include "EnemyState.h"

class FollowingState : public EnemyState {
public:
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Enemy& enemy, sf::RenderWindow& window, float delta, const Level& level);
    virtual void Enter(Enemy& enemy);
};

#endif

