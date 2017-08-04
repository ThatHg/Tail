#include "BreedComponent.h"

BreedComponent::BreedComponent() {
}

void BreedComponent::SetHealth(float health) {
    m_health = health;
}

void BreedComponent::SetSpeed(float speed) {
    m_speed = speed;
}

float BreedComponent::Health() {
    return m_health;
}

float BreedComponent::Speed() {
    return m_speed;
}
