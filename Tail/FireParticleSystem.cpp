#include "FireParticleSystem.h"

#include "GameTime.h"
#include "AssetsManager.h"
#include "Helper.h"
#include <cassert>

FireParticleSystem::FireParticleSystem(float width, const sf::Vector2f& position) {
    m_width = width;
    m_position = position;
    m_activeCount = 0;
    m_spriteParticle.setTexture(AssetsManager::Ref().GetTexture("fire_particle.png"));
    m_isActive = false;
    m_spawnDelay = 0.001f;
}

FireParticleSystem::~FireParticleSystem() {
}

void FireParticleSystem::Update(const GameTime & gametTime) {
    if (m_isActive) {
        float speed = 10.0f;
        float time = (float)gametTime.Time();
        if (time - m_time > m_spawnDelay) {
            m_time = time;
            Create(
                (int)Random(490.0f, 1590.0f),
                m_position + sf::Vector2f(Random(-m_width, m_width), 0.0f),
                sf::Vector2f(Random(-1.0f, 1.0f), (m_activeCount % 2) == 0 ? Random(-5.0f, -1.0f) * speed : Random(1.0f, 5.0f) * speed));
        }
    }
}

void FireParticleSystem::FixedUpdate(float delta) {
    if (m_isActive) {
        for (int i = 0; i < m_activeCount; i++) {
            m_particles[i].AddForce(sf::Vector2f(Random(-1.0, 1.0), 0));
            if (m_particles[i].FixedUpdate(delta)) {
                DeactivateParticle(i);
            }
        }
    }
}

void FireParticleSystem::Draw(sf::RenderWindow & window) {
    if (m_isActive) {
        for (int i = 0; i < m_activeCount; ++i) {
            sf::Uint8 c = (sf::Uint8)(255*(float)i / (float)m_activeCount);


            m_spriteParticle.setColor(sf::Color(c, c, 0, m_particles[i].Velocity().y <= 0 ? 255 : 60));
            m_spriteParticle.setPosition(m_particles[i].Position());
            window.draw(m_spriteParticle);
        }
    }
}

void FireParticleSystem::Activate() {
    m_activeCount = 0;
    m_isActive = true;
}

void FireParticleSystem::Deactivate() {
    m_activeCount = 0;
    m_isActive = false;
}

int FireParticleSystem::ActiveParticles() {
    return m_activeCount;
}

void FireParticleSystem::Create(int lifetime, const sf::Vector2f& start_pos, const sf::Vector2f& start_vel) {
    if (m_activeCount < MAX_PARTICLES) {
        m_particles[m_activeCount].Init(lifetime, start_pos, start_vel);
        ActivateParticle(m_activeCount);
    }
}

void FireParticleSystem::ActivateParticle(int index) {
    // Shouldn't already be active!
    assert(index >= m_activeCount);

    // Swap it with the first inactive particle
    // right after the active ones.
    Particle temp = m_particles[m_activeCount];
    m_particles[m_activeCount] = m_particles[index];
    m_particles[index] = temp;

    // Now there's one more.
    m_activeCount++;
}

void FireParticleSystem::DeactivateParticle(int index) {
    // Shouldn't already be inactive!
    assert(index < m_activeCount);

    // There's one fewer.
    m_activeCount--;

    // Swap it with the last active particle
    // right before the inactive ones.
    Particle temp = m_particles[m_activeCount];
    m_particles[m_activeCount] = m_particles[index];
    m_particles[index] = temp;
}
