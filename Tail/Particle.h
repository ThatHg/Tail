#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\System\Vector2.hpp>

class GameTime;

class Particle {
public:
    Particle();
    bool Active() const;
    void Update();
    bool FixedUpdate(const GameTime& gameTime);
    void Init(int lifetime, float x, float y, float xVel, float yVel);
    sf::Vector2f Position() const;
    sf::Vector2f Velocity() const;
    Particle* Next() const;
    void SetNext(Particle* next);

private:
    union {
        struct {
            float x,y;
            float xVel, yVel;
        } live;
        Particle* next;
    } m_state;

    float m_framesLeft;
};

#endif
