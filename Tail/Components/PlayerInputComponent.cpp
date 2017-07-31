#include <cassert>
#include "PlayerInputComponent.h"
#include "PhysicsComponent.h"
#include "../Entity.h"
#include "../Helper.h"

PlayerInputComponent::PlayerInputComponent() {
}

PlayerInputComponent::~PlayerInputComponent() {
}

void PlayerInputComponent::Update() {
    auto bindings = m_key_bindings.GetBindings();
    std::map<sf::Keyboard::Key, KeyBinding::Key>::iterator it;
    sf::Vector2f move_dir(0.0f, 0.0f);
    bool button_pressed = false;
    for (it = bindings.begin(); it != bindings.end(); it++) {
        if (sf::Keyboard::isKeyPressed(it->first)) {
            button_pressed = true;
            switch (it->second) {
            case KeyBinding::Key::UP:
                move_dir.y -= 1.0f;
                break;
            case KeyBinding::Key::DOWN:
                move_dir.y += 1.0f;
                break;
            case KeyBinding::Key::LEFT:
                move_dir.x -= 1.0f;
                break;
            case KeyBinding::Key::RIGHT:
                move_dir.x += 1.0f;
                break;
            default:
                break;
            }
        }
    }
    /*if (button_pressed == false) {
    move_dir = entity.GetTransform().Velocity() * -0.7f;
    }*/
    if (button_pressed) {
        auto physics = m_entity->GetComponent<PhysicsComponent>();
        assert(physics != nullptr);
        Normalize(move_dir);

        //LimitVelocity(new_velocity);
        physics->AddForce(move_dir * 100.0f, true);
    }
}

void PlayerInputComponent::FixedUpdate(sf::RenderWindow & window, double delta, const Level & level) {
}
