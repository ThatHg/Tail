#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML\Graphics\Vertex.hpp>

class Transform  {
public:
    Transform() :
        m_lookAt(sf::Vector2f(0.0f, 0.0f)),
        m_target(sf::Vector2f(0.0f, 0.0f)),
        m_position(sf::Vector2f(0.0f, 0.0f)),
        m_velocity(sf::Vector2f(0.0f, 0.0f)),
        m_rotation(0){
    }

    Transform(const Transform& t) {
        if (this != &t) {
            m_lookAt = t.LookAt();
            m_position = t.Position();
            m_velocity = t.Velocity();
            m_rotation = t.Rotation();
            m_target = t.Target();
        }
    }

    Transform& operator=(Transform& t) {
        if (this != &t) {
            m_lookAt = t.LookAt();
            m_position = t.Position();
            m_velocity = t.Velocity();
            m_rotation = t.Rotation();
            m_target = t.Target();
        }
        return *this;
    }

    // Get
    const sf::Vector2f& LookAt() const { return m_lookAt; }
    const sf::Vector2f& Target() const { return m_target; }
    const sf::Vector2f& Position() const { return m_position; }
    const sf::Vector2f& Velocity() const { return m_velocity; }
    float Rotation() const { return m_rotation; }

    // Set
    void SetLookAt(sf::Vector2f v) { m_lookAt = v; }
    void SetTarget(sf::Vector2f v) { m_target = v; }
    void SetPosition(sf::Vector2f v) { m_position = v; }
    void SetVelocity(sf::Vector2f v) { m_velocity = v; }
    void SetRotation(float v) { m_rotation = v; }
private:
    sf::Vector2f m_lookAt;
    sf::Vector2f m_target;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_rotation;
};

#endif // !TRANSFORM_H
