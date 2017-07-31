#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include "EnemyState.h"
#include "Level.h"

class BoidsState : public EnemyState {
public:
    BoidsState(double distance);
    virtual EnemyState* HandleCommand(Command command);
    virtual void Update(Enemy& enemy, sf::RenderWindow& window, double delta, const Level& level);
    virtual void Enter(Enemy& enemy);

private:
    sf::Vector2f Rule1(Level::Entities& e, Entity& enemy);
    sf::Vector2f Rule2(Level::Entities& e, Entity& enemy);
    sf::Vector2f Rule3(Level::Entities& e, Entity& enemy);
    sf::Vector2f Rule4(Enemy & enemy, sf::RenderWindow & window);
    sf::Vector2f Rule5(Enemy & enemy, const Level & level);
    double m_distance;
};

#endif // !BOIDS_STATE_H
