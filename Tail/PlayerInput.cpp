#include "PlayerInput.h"
#include <SFML\Window.hpp>
#include "Entity.h"
#include "Helper.h"

PlayerInput::PlayerInput() {
}

void LimitVelocity(sf::Vector2f& v) {
    double l = Length(v);
    float inv = (float)(l == 0.0 ? 1 : 1.0 / l);
    if (l > 300) {
        v = (v * inv) * 300.0f;
    }
}

void CapZero(sf::Vector2f& v) {
    double l = Length(v);
    float inv = (float)(l == 0.0 ? 1 : 1.0 / l);
    if (l < 10) {
        v = sf::Vector2f(0.0f, 0.0f);
    }
}

void PlayerInput::Update(Entity & entity, double delta) {
    std::map<sf::Keyboard::Key, KeyBinding::Key> bindings = _key_bindings.GetBindings();
    std::map<sf::Keyboard::Key, KeyBinding::Key>::iterator it;
    sf::Vector2f move_dir(0.0f, 0.0f);
    bool button_pressed = false;
    for (it = bindings.begin(); it != bindings.end(); it++) {
        if (sf::Keyboard::isKeyPressed(it->first) ){
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
    if (button_pressed == false) {
        move_dir = entity.GetTransform().Velocity() * -0.7f;
    }
    Normalize(move_dir);
    auto new_velocity = entity.GetTransform().Velocity() + move_dir * 50.0f;
    LimitVelocity(new_velocity);
    CapZero(new_velocity);
    entity.SetVelocity(new_velocity);
    
    entity.SetPosition(entity.GetTransform().Position() + entity.GetTransform().Velocity() * (float)delta);
}
