#include "Particle.h"
#include "GameTime.h"

Particle::Particle() :
    m_framesLeft(0) {
}

bool Particle::Active() const {
    return m_framesLeft > 0;
}

bool Particle::FixedUpdate(const GameTime& gametime) {
    if (!Active()) { return false; }

    m_state.live.x = m_state.live.x + m_state.live.xVel * (float)gametime.DeltaTime();
    m_state.live.y = m_state.live.y + m_state.live.yVel * (float)gametime.DeltaTime();

    m_framesLeft--;

    return m_framesLeft == 0;
}

void Particle::Init(int lifetime, float x, float y, float xVel, float yVel) {
    m_state.live.x = x;
    m_state.live.y = y;
    m_state.live.xVel = xVel;
    m_state.live.yVel = yVel;
    m_framesLeft = lifetime;
}

sf::Vector2f Particle::Position() const {
    return sf::Vector2f(m_state.live.x, m_state.live.y);
}

sf::Vector2f Particle::Velocity() const {
    return sf::Vector2f(m_state.live.xVel, m_state.live.yVel);
}

Particle * Particle::Next() const {
    return m_state.next;
}

void Particle::SetNext(Particle * next) {
    m_state.next = next;
}
