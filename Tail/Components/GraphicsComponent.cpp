#include "GraphicsComponent.h"
#include "../Entity.h"

GraphicsComponent::GraphicsComponent() {
}

void GraphicsComponent::Update() {
    const auto rect = GetEntity()->RectTransform();
    m_sprite.setPosition(rect.getPosition());
    m_sprite.setRotation(rect.getRotation());
}
void GraphicsComponent::FixedUpdate(sf::RenderWindow & , float , const Level &) {}

const sf::Sprite & GraphicsComponent::GetSprite() const {
    return m_sprite;
}

void GraphicsComponent::SetTexture(const sf::Texture & tex) {
    m_sprite.setTexture(tex);
}

void GraphicsComponent::SetRect(const sf::IntRect & rect) {
    m_sprite.setTextureRect(rect);
    m_sprite.setOrigin(sf::Vector2f((float)rect.width * 0.5f, (float)rect.height * 0.5f));
}

void GraphicsComponent::SetPosition(const sf::Vector2f & pos) {
    m_sprite.setPosition(pos);
}

void GraphicsComponent::SetRotation(float rot) {
    m_sprite.setRotation(rot);
}
