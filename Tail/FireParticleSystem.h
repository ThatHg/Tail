#ifndef FIRE_PARTICLE_SYSTEM_H
#define FIRE_PARTICLE_SYSTEM_H

#include <SFML\Graphics.hpp>
#include "ParticleSystem.h"
#include "Particle.h"
#include "Pool.h"

class FireParticleSystem : public ParticleSystem {
public:
    FireParticleSystem(float width, const sf::Vector2f& pos, const sf::Color& color);
    virtual ~FireParticleSystem();

    virtual void Update(const GameTime & gametTime, const sf::RenderWindow& window);
    virtual void FixedUpdate(float delta);
    virtual void Draw(sf::RenderWindow& window);
    virtual void Activate();
    virtual void Deactivate();
    virtual int ActiveParticles();

private:
    static const int MAX_PARTICLES = 5000;

    void Create(int lifetime, const sf::Vector2f& start_pos, const sf::Vector2f& start_vel);
    Pool m_particles;
    sf::Sprite m_spriteParticle;
    sf::Vector2f m_position;
    sf::Vector2f m_originalPos;
    sf::Shader m_fireParticleShader;
    float m_width;
    float m_spawnDelay;
    float m_time;
    bool m_isActive;
};

#endif // !FIRE_PARTICLE_SYSTEM_H

