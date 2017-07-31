#include "PlayerInput.h"
#include <SFML\Window.hpp>
#include "Entity.h"
#include "Helper.h"

PlayerInput::PlayerInput() {
}

void PlayerInput::Update(Entity & entity, double delta) {
    std::map<sf::Keyboard::Key, KeyBinding::Key> bindings = _key_bindings.GetBindings();
    std::map<sf::Keyboard::Key, KeyBinding::Key>::iterator it;
    sf::Vector2f move_dir(0.0f, 0.0f);
    for (it = bindings.begin(); it != bindings.end(); it++) {
        if (sf::Keyboard::isKeyPressed(it->first) ){
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
    Normalize(move_dir);
    
    entity.SetPosition(entity.GetTransform().Position() + move_dir * (float)delta * 500.0f);
}
