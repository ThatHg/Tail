#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

class Entity
{
public:
    virtual ~Entity();
    virtual void Update(sf::RenderWindow& window, double delta);
    const sf::Sprite& GetSprite() const;
    const sf::Vector2f&	GetLookAt() const;
    const sf::Vector2f& GetTarget() const;
    const sf::Vector2f&	GetPosition() const;
    const float GetRotation() const;

    void SetSprite(const std::string& spriteName);
    void SetSprite(const sf::Sprite& sprite);
    void SetLookAt(const sf::Vector2f& lookAt);
    void SetTarget(const sf::Vector2f& target);
    void SetPosition(const sf::Vector2f& position);
    void SetRotation(const float rotation);

protected:
    Entity();

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_lookAt;
    sf::Vector2f m_target;
    sf::Vector2f m_position;
    float m_rotation;
};
#endif