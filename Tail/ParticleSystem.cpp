#include "ParticleSystem.h"
#include <iostream>
#include "Helper.h"
#include "AssetsManager.h"

ParticleSystem::ParticleSystem() {
    // Init next particle to first position in particle array.
    m_nextParticle = &m_particles[0];

    // Init all particles to point to eachother in the array sequentially.
    for (size_t i = 0; i < MAX_PARTICLES - 1; i++) {
        m_particles[i].SetNext(&m_particles[i + 1]);
    }

    // Terminate the list with NULL as the last pointer value
    m_particles[MAX_PARTICLES - 1].SetNext(nullptr);

    m_spriteParticle.setTexture(AssetsManager::Ref().GetTexture("particle.png"));
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::FixedUpdate(const GameTime & gametTime) {
    for (size_t i = 0; i < MAX_PARTICLES; i++) {
        if (m_particles[i].FixedUpdate(gametTime)) {
            m_particles[i].SetNext(m_nextParticle);
        }
    }
}

void ParticleSystem::Draw(sf::RenderWindow & window) {
    for (size_t i = 0; i < MAX_PARTICLES; ++i) {
        if (!m_particles[i].Active()) { continue; }
        m_spriteParticle.setPosition(m_particles[i].Position());
        window.draw(m_spriteParticle);
    }
}

void ParticleSystem::SpawnParticles() {
    const int particles_count = 1000;
    const float inverse_count = 360.0f / particles_count;
    const float speed = 600.0f;
    for (size_t i = 0; i < particles_count; i++) {
        float xv = std::cos(i * inverse_count);
        float yv = std::sin(i * inverse_count);
        Create(30000, 300.0f, 300.0f, xv * speed, yv * speed);
    }
}

void ParticleSystem::Create(float lifetime, float x, float y, float xVel, float yVel) {
    if (m_nextParticle == nullptr) {
        std::cerr << "Error creating particle: you have reached MAX_PARTICLES" << std::endl;
        return;
    }
    Particle *particle = m_nextParticle;
    m_nextParticle = particle->Next();
    particle->Init(lifetime, x, y, xVel, yVel);
}
