#ifndef BREED_COMPONENT_H
#define BREED_COMPONENT_H

#include "Component.h"

class BreedComponent : public Component {
public:
    BreedComponent();
    void SetHealth(float health);
    void SetSpeed(float speed);
    float Health();
    float Speed();
private:
    float m_health;
    float m_speed;
};

#endif
