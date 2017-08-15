#include "FireParticleSystem.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "GameTime.h"
#include "AssetsManager.h"
#include "Helper.h"

FireParticleSystem::FireParticleSystem(float width, const sf::Vector2f& position, const sf::Color& color) {
    m_width = width;
    m_originalPos = m_position = position;
    m_spriteParticle.setTexture(AssetsManager::Ref().GetTexture("fire_sample_map.png"));
    m_spriteParticle.setTextureRect(sf::IntRect(0, 0, 8, 8));
    const auto tex_size = m_spriteParticle.getTexture()->getSize();
    m_spriteParticle.setOrigin(4, 8);
    m_isActive = false;
    m_spawnDelay = 0.001f;
    m_fireParticleShader.loadFromFile("Resources/Shaders/circle_gradient.vert", "Resources/Shaders/circle_gradient.frag");
    m_spriteParticle.setColor(color);
    m_time = 0;
}

FireParticleSystem::~FireParticleSystem() {
}

void FireParticleSystem::Update(const GameTime & gameTime, const sf::RenderWindow& window) {
    if (m_isActive) {
        float y_speed = 50.0f;
        float x_speed = 20.0f;
        float time = (float)gameTime.Time();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mpos((float)mousePosition.x, (float)mousePosition.y);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            m_position = mpos;
        }
        else {
            float pi_time = time * PI * 2;
            m_position = m_originalPos + sf::Vector2f(sin(pi_time), -cos(pi_time)) * 100.0f;
        }

        m_fireParticleShader.setUniform("_middle_point", m_position);
        m_fireParticleShader.setUniform("u_resolution", sf::Vector2f(window.getSize()));
        m_fireParticleShader.setUniform("u_mouse", mpos);
        m_fireParticleShader.setUniform("u_time", time);

        if (time - m_time > m_spawnDelay) {
            m_time = time;
            Create(
                (int)Random(30.0f, 590.0f),
                sf::Vector2f(Random(-m_width, m_width) + m_position.x, m_position.y),
                sf::Vector2f(Random(-1.0f, 1.0f) * x_speed, Random(-1.0f, 0.0f) * y_speed));
        }
    }
}

void FireParticleSystem::FixedUpdate(float delta) {
    if (m_isActive) {
        int num_active = m_particles.NumActive();
        for (int i = 0; i < num_active; i++) {
            m_particles[i].AddForce(sf::Vector2f(Random(-1.0, 1.0), 0));
            if (m_particles[i].FixedUpdate(delta)) {
                m_particles.Deactivate(i);
            }
        }
    }
}

void FireParticleSystem::Draw(sf::RenderWindow & window) {
    if (m_isActive) {
        int num_active = m_particles.NumActive();
        for (int i = 0; i < num_active; ++i) {
            float start_time = (float)m_particles[i].StartTime();
            float curr_time = (float)m_particles[i].Time();
            m_fireParticleShader.setUniform("u_ratio_time", curr_time / start_time);
            m_spriteParticle.setPosition(m_particles[i].Position().x, m_particles[i].Position().y);
            float timeScale = ( (float)m_particles[i].Time() / (float)m_particles[i].StartTime() ) * 2.0f;
            m_spriteParticle.setScale(timeScale, timeScale);
            window.draw(m_spriteParticle, &m_fireParticleShader);
        }
    }
    else {
        std::printf("Not active\n");
    }
}

void FireParticleSystem::Activate() {
    m_particles.Reset();
    m_isActive = true;
}

void FireParticleSystem::Deactivate() {
    m_particles.Reset();
    m_isActive = false;
}

int FireParticleSystem::ActiveParticles() {
    return m_particles.NumActive();
}

void FireParticleSystem::Create(int lifetime, const sf::Vector2f& start_pos, const sf::Vector2f& start_vel) {
    if (m_particles.NumActive() < MAX_PARTICLES) {
        m_particles.ActivateNext().Init(lifetime, start_pos, start_vel);
    }
}

//void FireParticleSystem::ActivateParticle(int index) {
//    // Shouldn't already be active!
//    assert(index >= m_activeCount);
//
//    // Swap it with the first inactive particle
//    // right after the active ones.
//    Particle temp = m_particles[m_activeCount];
//    m_particles[m_activeCount] = m_particles[index];
//    m_particles[index] = temp;
//
//    // Now there's one more.
//    m_activeCount++;
//}
//
//void FireParticleSystem::DeactivateParticle(int index) {
//    // Shouldn't already be inactive!
//    assert(index < m_activeCount);
//
//    // There's one fewer.
//    m_activeCount--;
//
//    // Swap it with the last active particle
//    // right before the inactive ones.
//    Particle temp = m_particles[m_activeCount];
//    m_particles[m_activeCount] = m_particles[index];
//    m_particles[index] = temp;
//}
