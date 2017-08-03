#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemyState.h"

class Breed;
class RenderWindow;

class Enemy : public Entity {
    friend class Breed;
public:
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level);
    virtual void HandleCommand(Command command);

    const bool IsAlive() const;
    const float GetHealth() const;
    const float GetWalkingSpeed() const;
    const std::string& GetFollowingSprite() const;
    const std::string& GetIdlingSprite() const;
private:
    Enemy(Breed& breed);
    Breed& m_breed;
    float m_health;
    EnemyState* m_state;
};

#endif
