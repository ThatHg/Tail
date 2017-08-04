#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>

class Component;
class Entity;
class Level;

class Component {
public:
    virtual ~Component();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level);
    void SetEntity(Entity* entity);
    Entity* GetEntity() const;
private:
    Entity* m_entity;
};

#endif
