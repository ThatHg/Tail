#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\System\Vector3.hpp>

class GameTime;
class Particle {
public:
    Particle();
    bool Active() const;
    void Update();
    bool FixedUpdate(float delta);
    void Move(const sf::Vector3f& offset);
    void AddForce(const sf::Vector3f& force);
    void Init(int lifetime, const sf::Vector3f& start_pos, const sf::Vector3f& start_vel);
    const sf::Vector3f& Position() const;
    const sf::Vector3f& Velocity() const;
    int Time() const;
    int StartTime() const;

private:
    sf::Vector3f m_position;
    sf::Vector3f m_velocity;
    int m_framesLeft;
    int m_originalFrames;
};

#endif
