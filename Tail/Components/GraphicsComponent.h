#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include <SFML\Graphics\Sprite.hpp>

#include "Component.h"

class GraphicsComponent : public Component {
public:
    GraphicsComponent();
    virtual void Update();
    const sf::Sprite& GetSprite() const;
    void SetTexture(const sf::Texture& tex);
    void SetRect(const sf::IntRect& rect);
    void SetPosition(const sf::Vector2f& pos);
    void SetRotation(float rot);
private:
    sf::Sprite m_sprite;
};

#endif
