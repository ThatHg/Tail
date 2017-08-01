#include "Enemy.h"
#include "Breed.h"
#include "AssetsManager.h"
#include "BoidsState.h"

Enemy::Enemy(Breed & breed) :
    m_breed(breed),
    m_health(breed.GetHealth()),
    m_state(new BoidsState(100.0)),
    Entity() {
    SetSprite(sf::Sprite(AssetsManager::Ref().GetTexture(breed.GetIdlingSprite())));
    m_state->Enter(*this);
}

void Enemy::FixedUpdate(sf::RenderWindow& window, float delta, const Level& level) {
    m_state->Update(*this, window, delta, level);
}

void Enemy::HandleCommand(Command command) {
    EnemyState* newState = m_state->HandleCommand(command);
    if (newState != NULL) {
        // Cleanup before switching state
        delete m_state;
        m_state = newState;
        m_state->Enter(*this);
    }
}

const bool Enemy::IsAlive() const {
    return m_health > 0.0;
}

const float Enemy::GetHealth() const {
    return m_health;
}

const float Enemy::GetWalkingSpeed() const {
    return m_breed.GetWalkingSpeed();
}

const std::string& Enemy::GetFollowingSprite() const {
    return m_breed.GetFollowingSprite();
}

const std::string& Enemy::GetIdlingSprite() const {
    return m_breed.GetIdlingSprite();
}


