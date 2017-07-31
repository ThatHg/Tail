#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include "TransformComponent.h"
class Animation;
class Level;

class Entity
{
public:
    virtual ~Entity();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, double delta, const Level& level);
    const sf::Sprite& GetSprite() const;
    const TransformComponent& GetTransform() const;

    void SetSprite(const std::string& spriteName);
    void SetSprite(const sf::Sprite& sprite);
    void SetLookAt(const sf::Vector2f& lookAt);
    void SetTarget(const sf::Vector2f& target);
    void SetPosition(const sf::Vector2f& position);
    void SetVelocity(const sf::Vector2f& velocity);
    void SetRotation(const float rotation);

protected:
    Entity();
    Animation* m_animation;

private:
    sf::Sprite m_sprite;
    TransformComponent m_transform;
};
#endif