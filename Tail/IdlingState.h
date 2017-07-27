#ifndef IDLING_STATE_H
#define IDLING_STATE_H

#include "EnemyState.h"
#include "Helper.h"

class Enemy;

class IdlingState : public EnemyState {
public:
    IdlingState();
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Enemy& enemy, sf::RenderWindow& window, double delta);
    virtual void Enter(Enemy& enemy);
private:
    double m_idlingTimer;
};

#endif