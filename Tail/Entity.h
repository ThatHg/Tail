#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include "Transform.h"
#include <cassert>
class Animation;
class Level;
class Component;

class Entity
{
public:
    virtual ~Entity();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, double delta, const Level& level);
    const sf::Sprite& GetSprite() const;
    const Transform& GetTransform() const;

    void SetSprite(const std::string& spriteName);
    void SetSprite(const sf::Sprite& sprite);
    void SetLookAt(const sf::Vector2f& lookAt);
    void SetTarget(const sf::Vector2f& target);
    void SetPosition(const sf::Vector2f& position);
    void SetVelocity(const sf::Vector2f& velocity);
    void SetRotation(const float rotation);

    template <typename T> bool Has() const { return Has(typeid(T).hash_code()); }
    bool Has(std::size_t key) const { return m_components.find(key) != m_components.end(); }

    template <typename T> T* AddComponent() { return AddComponent<T>( typeid(T).hash_code()); }
    template <typename T> T* AddComponent(std::size_t key);
    void AddComponent(std::size_t key, Component* comp);

    template <typename T> T* GetComponent() const { return GetComponent<T>(typeid(T).hash_code()); }
    template <typename T> T* GetComponent(std::size_t key) const;
protected:
    Entity();
    Animation* m_animation;

private:
    std::map<std::size_t, Component*> m_components;
    sf::Sprite m_sprite;
    Transform m_transform;
};

template <typename T> T* Entity::AddComponent(std::size_t key){
    const auto comp = new T();
    AddComponent(key, comp);
    return comp;
};

template <typename T> T* Entity::GetComponent(std::size_t key) const {
#if _DEBUG
    // All components must be present
    const auto found = Has(key);
    assert(found);
#endif
    const auto it = m_components.find(key);
    return it == m_components.end() ? nullptr : (T*)it->second;
}

#endif
