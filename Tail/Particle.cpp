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

void Particle::Move(const sf::Vector3f & offset) {
    m_position = m_position + offset;
}

void Particle::AddForce(const sf::Vector3f & force) {
    m_velocity = m_velocity + force;
}

void Particle::Init(int lifetime, const sf::Vector3f & pos, const sf::Vector3f & vel) {
    m_position = pos;
    m_velocity = vel;
    m_framesLeft = lifetime;
    m_originalFrames = lifetime;
}

const sf::Vector3f& Particle::Position() const {
    return m_position;
}

const sf::Vector3f& Particle::Velocity() const {
    return m_velocity;
}

int Particle::Time() const {
    return m_framesLeft;
}

int Particle::StartTime() const {
    return m_originalFrames;
}
