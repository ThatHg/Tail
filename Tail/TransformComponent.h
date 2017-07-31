#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <SFML\Graphics\Vertex.hpp>

class TransformComponent {
public:
    TransformComponent() :
        m_lookAt(sf::Vector2f(0.0f, 0.0f)),
        m_target(sf::Vector2f(0.0f, 0.0f)),
        m_position(sf::Vector2f(0.0f, 0.0f)),
        m_rotation(0){
    }

    TransformComponent(const TransformComponent& t) {
        if (this != &t) {
            m_lookAt = t.LookAt();
            m_position = t.Position();
            m_rotation = t.Rotation();
            m_target = t.Target();
        }
    }

    TransformComponent& operator=(TransformComponent& t) {
        if (this != &t) {
            m_lookAt = t.LookAt();
            m_position = t.Position();
            m_rotation = t.Rotation();
            m_target = t.Target();
        }
        return *this;
    }

    // Get
    const sf::Vector2f& LookAt() const { return m_lookAt; }
    const sf::Vector2f& Target() const { return m_target; }
    const sf::Vector2f& Position() const { return m_position; }
    float Rotation() const { return m_rotation; }

    // Set
    void SetLookAt(sf::Vector2f v) { m_lookAt = v; }
    void SetTarget(sf::Vector2f v) { m_target = v; }
    void SetPosition(sf::Vector2f v) { m_position = v; }
    void SetRotation(float v) { m_rotation = v; }
private:
    sf::Vector2f m_lookAt;
    sf::Vector2f m_target;
    sf::Vector2f m_position;
    float m_rotation;
};

#endif // !TRANSFORM_COMPONENT_H
