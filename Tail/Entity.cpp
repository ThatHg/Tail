#include "Entity.h"
#include "AssetsManager.h"
#include "Components\Component.h"

Entity::Entity() {
    m_rectTransform = sf::RectangleShape(sf::Vector2f(64.0f, 64.0f));
    m_rectTransform.setOrigin(sf::Vector2f(
        m_rectTransform.getGlobalBounds().width * 0.5f,
        m_rectTransform.getGlobalBounds().height * 0.5f));
}

Entity::~Entity(){
    for (const auto component : m_components) {
        delete component.second;
    }
}

void Entity::Update() {
    for (const auto itr : m_components) {
        itr.second->Update();
    }
}

void Entity::FixedUpdate(sf::RenderWindow& window, float delta, const Level& level) {
    for (const auto itr : m_components) {
        itr.second->FixedUpdate(window, delta, level);
    }
}

void Entity::AddComponent(std::size_t key, Component* component) {
    m_components[key] = component;
    component->SetEntity(this);
}