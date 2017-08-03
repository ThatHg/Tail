#include "PhysicsComponent.h"
#include "../Entity.h"
#include "../Helper.h"

PhysicsComponent::PhysicsComponent() :
m_gravity_enabled(false),
m_velocity(sf::Vector2f(0.0f, 0.0f)),
m_angularVelocity(0.0f){
}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::Update() {
}

void PhysicsComponent::FixedUpdate(sf::RenderWindow&, float delta, const Level&) {
    if (m_gravity_enabled) {
        AddForce(sf::Vector2f(0, 1), false);
    }
    GetEntity()->RectTransform().move(m_velocity * delta);
    GetEntity()->RectTransform().rotate(m_angularVelocity * delta);
}

void PhysicsComponent::EnableGravity(bool enabled) {
    m_gravity_enabled = enabled;
}

void PhysicsComponent::AddForce(const sf::Vector2f & force, bool is_impulse) {
    if (is_impulse) {
        m_velocity = force;
    }
    else {
        m_velocity += force;
    }
}

void PhysicsComponent::AddForce(const sf::Vector2f & force, const sf::Vector2f & pos, bool is_impulse) {
    auto center = GetEntity()->RectTransform().getPosition();
    auto relVec = pos - center;
    auto cross = Cross(relVec, force);
    if (is_impulse) {
        m_angularVelocity = Length(cross);
    }
    else {
        m_angularVelocity += Length(cross);
    }
}

void PhysicsComponent::SetPosition(const sf::Vector2f pos) {
    GetEntity()->RectTransform().setPosition(pos);
}
