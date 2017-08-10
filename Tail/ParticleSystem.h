#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SFML\Graphics\RenderWindow.hpp>

class GameTime;

class ParticleSystem {
public:
    virtual ~ParticleSystem() {};

    virtual void Update(const GameTime& gametTime) = 0;
    virtual void FixedUpdate(float delta) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual int ActiveParticles() { return 0; }
};

#endif // !PARTICLE_SYSTEM_H

