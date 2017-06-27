#ifndef BREED_H
#define BREED_H

#include <string>

class Enemy;

class Breed {
public:
    Breed(double health, double walkingSpeed, const std::string& idlingSprite, const std::string& followingSprite);
    Enemy* NewEnemy();

    double GetWalkingSpeed();
    double GetHealth();
    const std::string& GetFollowingSprite() const;
    const std::string& GetIdlingSprite() const;
private:
    double m_health;
    double m_walkingSpeed;
    const std::string m_idlingSprite;
    const std::string m_followingSprite;
};

#endif

