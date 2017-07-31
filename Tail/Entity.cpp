#include "Entity.h"
#include "AssetsManager.h"
#include "Animation.h"

Entity::Entity() :
    m_lookAt(sf::Vector2f(0.0f, 1.0f)),
    m_target(sf::Vector2f(640.0f, 360.0f)),
    m_position(sf::Vector2f(-900.0f, -900.0f)),
    m_rotation(0),
    m_animation(nullptr)
{
}

Entity::~Entity()
{}

void Entity::Update() {
}

void Entity::FixedUpdate(sf::RenderWindow& window, double delta, const Level& level) {
}

const sf::Sprite& Entity::GetSprite() const {
    return m_animation == nullptr ? m_sprite : m_animation->GetCurrentFrame();
}

const sf::Vector2f& Entity::GetLookAt() const {
    return m_lookAt;
}

const sf::Vector2f& Entity::GetTarget() const {
    return m_target;
}

const sf::Vector2f&	Entity::GetPosition() const {
    return m_position;
}

const float Entity::GetRotation() const {
    return m_rotation;
}

void Entity::SetSprite(const std::string& spriteName) {
    m_sprite.setTexture(AssetsManager::Ref().GetTexture(spriteName));
}

void Entity::SetSprite(const sf::Sprite& sprite) {
    m_sprite = sprite;
}

void Entity::SetLookAt(const sf::Vector2f& lookAt) {
    m_lookAt = lookAt;
}

void Entity::SetTarget(const sf::Vector2f& target) {
    m_target = target;
}

void Entity::SetPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
    if (m_animation != nullptr) {
        m_animation->SetPosition(position);
    }
    m_position = position;
}

void Entity::SetRotation(const float rotation) {
    m_sprite.setRotation(rotation);
    m_rotation = rotation;
}