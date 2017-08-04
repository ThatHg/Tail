#include "Component.h"
#include <cassert>

Component::~Component() {
}

void Component::Update() {
}

void Component::FixedUpdate(sf::RenderWindow &, float, const Level &) {
}

void Component::SetEntity(Entity * entity) {
    m_entity = entity;
}

Entity * Component::GetEntity() const {
#ifdef _DEBUG
    assert(m_entity != nullptr && "Entity should never be nullptr.");
#endif
    return m_entity;
}
