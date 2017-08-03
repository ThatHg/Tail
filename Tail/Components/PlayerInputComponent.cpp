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

    const auto physics = GetEntity()->GetComponent<PhysicsComponent>();

    if (button_pressed == false) {
        physics->AddForce(sf::Vector2f(physics->Velocity().x * -0.01f, 0), false);
    }
    else {
        Normalize(move_dir);
        physics->AddForce(move_dir * 500.0f, true);
    }
   
}

void PlayerInputComponent::FixedUpdate(sf::RenderWindow &, float, const Level &) {
}
