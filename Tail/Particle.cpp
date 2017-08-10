#include "Particle.h"
#include "GameTime.h"

Particle::Particle() :
    m_framesLeft(0) {
}

bool Particle::Active() const {
    return m_framesLeft > 0;
}

bool Particle::FixedUpdate(float delta) {
    m_position = m_position + m_velocity * delta;
    m_framesLeft--;
    return m_framesLeft == 0;
}

void Particle::Move(const sf::Vector2f & offset) {
    m_position = m_position + offset;
}

void Particle::AddForce(const sf::Vector2f & force) {
    m_velocity = m_velocity + force;
}

void Particle::Init(int lifetime, const sf::Vector2f & pos, const sf::Vector2f & vel) {
    m_position = pos;
    m_velocity = vel;
    m_framesLeft = lifetime;
}

sf::Vector2f Particle::Position() const {
    return m_position;
}

sf::Vector2f Particle::Velocity() const {
    return m_velocity;
}