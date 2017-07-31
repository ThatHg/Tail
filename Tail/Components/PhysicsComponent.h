#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent();
    ~PhysicsComponent();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, double delta, const Level& level);
    
    sf::Vector2f Velocity() { return m_velocity; }

    void EnableGravity(bool enabled);
    void AddForce(const sf::Vector2f& force, bool is_impulse);
private:
    bool m_gravity_enabled;
    sf::Vector2f m_velocity;
};

#endif