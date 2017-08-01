#include "Entity.h"
#include "AssetsManager.h"
#include "Animation.h"
#include "Components\Component.h"

Entity::Entity() :
    m_transform(Transform()),
    m_animation(nullptr){
}

Entity::~Entity(){
    std::map<size_t, Component*>::iterator itr;
    for (itr = m_components.begin(); itr != m_components.end(); itr++) {
        delete itr->second;
    }
}

void Entity::Update() {
    std::map<size_t, Component*>::iterator itr;
    for (itr = m_components.begin(); itr != m_components.end(); itr++) {
        itr->second->Update();
    }
}

void Entity::FixedUpdate(sf::RenderWindow& window, float delta, const Level& level) {
    std::map<size_t, Component*>::iterator itr;
    for (itr = m_components.begin(); itr != m_components.end(); itr++) {
        itr->second->FixedUpdate(window, delta, level);
    }
}

const sf::Sprite& Entity::GetSprite() const {
    return m_animation == nullptr ? m_sprite : m_animation->GetCurrentFrame();
}

const Transform & Entity::GetTransform() const {
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

void Entity::SetVelocity(const sf::Vector2f& velocity) {
    m_transform.SetVelocity(velocity);
}

void Entity::SetRotation(const float rotation) {
    m_sprite.setRotation(rotation);
    m_transform.SetRotation(rotation);
}

void Entity::AddComponent(std::size_t key, Component* component) {
    m_components[key] = component;
    component->SetEntity(this);
}