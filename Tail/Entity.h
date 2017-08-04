#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <cassert>
class Animation;
class Level;
class Component;

class Entity
{
public:
    Entity();
    virtual ~Entity();
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level);

    sf::RectangleShape& RectTransform() { return m_rectTransform; }
    const sf::RectangleShape& RectTransform() const { return m_rectTransform; }

    template <typename T> bool Has() const { return Has(typeid(T).hash_code()); }
    bool Has(std::size_t key) const { return m_components.find(key) != m_components.end(); }

    template <typename T> T* AddComponent() { return AddComponent<T>( typeid(T).hash_code()); }
    template <typename T> T* AddComponent(std::size_t key);
    void AddComponent(std::size_t key, Component* comp);

    template <typename T> T* GetComponent() const { return GetComponent<T>(typeid(T).hash_code()); }
    template <typename T> T* GetComponent(std::size_t key) const;
private:
    sf::RectangleShape m_rectTransform;
    std::map<std::size_t, Component*> m_components;
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
    assert(found && "Failed all components must be present.");
#endif
    const auto it = m_components.find(key);
    return (T*)it->second;
}

#endif
