#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>
#include <cassert>

class Component;
class Entity;
class Level;

class Component {
public:
    virtual ~Component() {}
    virtual void Update() = 0;
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level) = 0;
    void SetEntity(Entity* entity) { m_entity = entity; };
    Entity* GetEntity() const {
#ifdef _DEBUG
        assert(m_entity != nullptr && "Entity should never be nullptr.");
#endif
        return m_entity;
    }
private:
    Entity* m_entity;
};

#endif
