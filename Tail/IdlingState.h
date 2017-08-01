#ifndef IDLING_STATE_H
#define IDLING_STATE_H

#include "EnemyState.h"

class Enemy;

class IdlingState : public EnemyState {
public:
    IdlingState();
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Enemy& enemy, sf::RenderWindow& window, float delta, const Level& level);
    virtual void Enter(Enemy& enemy);
private:
    float m_idlingTimer;
};

#endif