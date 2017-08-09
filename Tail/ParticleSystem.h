#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include <SFML\Graphics.hpp>

static const int MAX_PARTICLES = 10000;

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    void FixedUpdate(const GameTime& gametTime);
    void Draw(sf::RenderWindow& window);
    void SpawnParticles();
    void Create(float lifetime, float x, float y, float xVel, float yVel);
private:
    sf::Sprite m_spriteParticle;
    Particle m_particles[MAX_PARTICLES];
    Particle* m_nextParticle;
};

#endif // !PARTICLE_SYSTEM_H

