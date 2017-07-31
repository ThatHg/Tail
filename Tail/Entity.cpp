#include "Entity.h"
#include "AssetsManager.h"
#include "Animation.h"

Entity::Entity() :
    m_transform(TransformComponent()),
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

const TransformComponent & Entity::GetTransform() const {
    return m_transform;
}

void Entity::SetSprite(const std::string& spriteName) {
    m_sprite.setTexture(AssetsManager::Ref().GetTexture(spriteName));
}

void Entity::SetSprite(const sf::Sprite& sprite) {
    m_sprite = sprite;
}

void Entity::SetLookAt(const sf::Vector2f& lookAt) {
    m_transform.SetLookAt(lookAt);
}

void Entity::SetTarget(const sf::Vector2f& target) {
    m_transform.SetTarget(target);
}

void Entity::SetPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
    if (m_animation != nullptr) {
        m_animation->SetPosition(position);
    }
    m_transform.SetPosition(position);
}

void Entity::SetRotation(const float rotation) {
    m_sprite.setRotation(rotation);
    m_transform.SetRotation(rotation);
}