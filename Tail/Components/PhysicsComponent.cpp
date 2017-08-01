#include "PhysicsComponent.h"
#include "../Entity.h"
#include <iostream>

PhysicsComponent::PhysicsComponent() :
m_gravity_enabled(false) {
}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::Update() {
}

void PhysicsComponent::FixedUpdate(sf::RenderWindow&, float delta, const Level&) {
    if (m_gravity_enabled) {
        AddForce(sf::Vector2f(0, 1), false);
    }
    Transform t = m_entity->GetTransform();
    m_entity->SetPosition(t.Position() + m_velocity * delta);
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
