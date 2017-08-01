#ifndef BREED_H
#define BREED_H

#include <string>

class Enemy;

class Breed {
public:
    Breed(float health, float walkingSpeed, const std::string& idlingSprite, const std::string& followingSprite);
    Enemy* NewEnemy();

    float GetWalkingSpeed();
    float GetHealth();
    const std::string& GetFollowingSprite() const;
    const std::string& GetIdlingSprite() const;
private:
    float m_health;
    float m_walkingSpeed;
    const std::string m_idlingSprite;
    const std::string m_followingSprite;
};

#endif

