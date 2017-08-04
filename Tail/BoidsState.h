#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include "EnemyState.h"
#include "Level.h"

class PhysicsComponent;

class BoidsState : public EnemyState {
public:
    BoidsState(float distance);
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Entity& enemy, sf::RenderWindow& window, float delta, const Level& level);
    virtual void Enter(Entity& enemy);

private:
    sf::Vector2f Rule1(Level::Entities& e, Entity& enemy);
    sf::Vector2f Rule2(Level::Entities& e, Entity& enemy);
    sf::Vector2f Rule3(Level::Entities& e, Entity& enemy, PhysicsComponent* pc);
    sf::Vector2f Rule4(Entity & enemy, sf::RenderWindow & window);
    sf::Vector2f Rule5(Entity & enemy, const Level & level);
    float m_distance;
};

#endif // !BOIDS_STATE_H
