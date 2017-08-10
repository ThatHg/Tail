#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\System\Vector2.hpp>

class GameTime;

class Particle {
public:
    Particle();
    bool Active() const;
    void Update();
    bool FixedUpdate(float delta);
    void Move(const sf::Vector2f& offset);
    void AddForce(const sf::Vector2f& force);
    void Init(int lifetime, const sf::Vector2f& start_pos, const sf::Vector2f& start_vel);
    sf::Vector2f Position() const;
    sf::Vector2f Velocity() const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    int m_framesLeft;
};

#endif
