#include "Breed.h"
#include "Enemy.h"

Breed::Breed(double health, double walkingSpeed, const std::string& idlingSprite, const std::string& followingSprite) :
    m_health(health),
    m_walkingSpeed(walkingSpeed),
    m_idlingSprite(idlingSprite),
    m_followingSprite(followingSprite) {
}

Enemy * Breed::NewEnemy() {
    return new Enemy(*this);
}

double Breed::GetWalkingSpeed() {
    return m_walkingSpeed;
}

double Breed::GetHealth() {
    return m_health;
}

const std::string& Breed::GetFollowingSprite() const {
    return m_followingSprite;
}

const std::string& Breed::GetIdlingSprite() const {
    return m_idlingSprite;
}
