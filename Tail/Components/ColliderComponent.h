#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "Component.h"

class ColliderComponent : public Component {
public:
    ColliderComponent();
    ~ColliderComponent();
private:
    sf::RectangleShape m_rect;
};

#endif
