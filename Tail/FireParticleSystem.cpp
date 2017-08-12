#include "FireParticleSystem.h"

#include <algorithm>
#include <cassert>

#include "GameTime.h"
#include "AssetsManager.h"
#include "Helper.h"

FireParticleSystem::FireParticleSystem(float width, const sf::Vector2f& position) {
    m_particles.resize(MAX_PARTICLES);
    m_width = width;
    m_position = position;
    m_activeCount = 0;
    m_spriteParticle.setTexture(AssetsManager::Ref().GetTexture("fire_sample_map.png"));
    m_spriteParticle.setTextureRect(sf::IntRect(0, 0, 8, 8));
    m_isActive = false;
    m_spawnDelay = 0.001f;
    m_fireParticleShader.loadFromFile("Resources/Shaders/circle_gradient.vert", "Resources/Shaders/circle_gradient.frag");
}

FireParticleSystem::~FireParticleSystem() {
}

void FireParticleSystem::Update(const GameTime & gametTime, const sf::RenderWindow&) {
    if (m_isActive) {
        m_fireParticleShader.setUniform("_middle_point", m_position);
        float speed = 50.0f;
        float z_speed = 50.0f;
        float x_speed = 20.0f;
        float time = (float)gametTime.Time();
        if (time - m_time > m_spawnDelay) {
            m_time = time;
            Create(
                (int)Random(30.0f, 590.0f),
                sf::Vector3f(Random(-m_width, m_width) + m_position.x, m_position.y,0),
                sf::Vector3f(Random(-1.0f, 1.0f) * x_speed, Random(-1.0f, 0.0f) * speed, Random(-1.0f, 1.0f) * z_speed));
        }
    }
}

bool cmp(const Particle& a, const Particle& b) {
    return a.Position().z < b.Position().z;
}

void FireParticleSystem::FixedUpdate(float delta) {
    if (m_isActive) {
        const auto start = m_particles.begin();
        std::partial_sort(start, start + m_activeCount, start + (int)(m_activeCount * 0.5f), cmp);
        for (int i = 0; i < m_activeCount; i++) {
            
            m_particles[i].AddForce(sf::Vector3f(Random(-1.0, 1.0), 0, Random(-1.0, 1.0)));
            if (m_particles[i].FixedUpdate(delta)) {
                DeactivateParticle(i);
            }
        }
    }
}

void FireParticleSystem::Draw(sf::RenderWindow & window) {
    if (m_isActive) {
        for (int i = 0; i < m_activeCount; ++i) {
            m_spriteParticle.setPosition(m_particles[i].Position().x, m_particles[i].Position().y);
            float timeScale = ( (float)m_particles[i].Time() / (float)m_particles[i].StartTime() ) * 2.0f;
            m_spriteParticle.setScale(timeScale, timeScale);
            m_fireParticleShader.setUniform("_z_pos", m_particles[i].Position().z);
            window.draw(m_spriteParticle, &m_fireParticleShader);
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

void FireParticleSystem::Create(int lifetime, const sf::Vector3f& start_pos, const sf::Vector3f& start_vel) {
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
