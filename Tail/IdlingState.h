#ifndef IDLING_STATE_H
#define IDLING_STATE_H

#include "EnemyState.h"

class IdlingState : public EnemyState {
public:
    IdlingState();
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Entity& enemy, sf::RenderWindow& window, float delta, const Level& level);
    virtual void Enter(Entity& enemy);
private:
    float m_idlingTimer;
};

#endif