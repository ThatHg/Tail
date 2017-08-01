#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>

class Component;
class Entity;
class Level;

class Component {
public:
    virtual ~Component() {}
    virtual void Update() = 0;
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level) = 0;
    void SetEntity(Entity* entity) { m_entity = entity; };
    Entity* GetEntity() const { return m_entity; }
protected:
    Entity* m_entity;
};

#endif
