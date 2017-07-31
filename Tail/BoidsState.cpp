#include "BoidsState.h"
#include "IdlingState.h"
#include "Level.h"
#include "Enemy.h"
#include "TransformComponent.h"
#include "Helper.h"

EnemyState * BoidsState::HandleCommand(Command command) {
    if (command == Command::IDLE) {
        return new IdlingState();
    }
    return NULL;
}

sf::Vector2f Rule1(Level::Entities& e, Entity& enemy) {
    sf::Vector2f center_of_mass(0.0f, 0.0f);
    int flock_size = 0;
    for (int i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            TransformComponent t = e[i]->GetTransform();
            if (Length(t.Position() - enemy.GetTransform().Position()) <= 100) {
                center_of_mass += t.Position();
                flock_size++;
            }
        }
    }
    float inverse = flock_size == 0 ? 1.0f : 1.0f / (float)flock_size;
    center_of_mass *= inverse;
    return ( center_of_mass - enemy.GetTransform().Position()) * 0.1f;
}

sf::Vector2f Rule2(Level::Entities& e, Entity& enemy) {
    /*for (int i = 0; i < e.size(); ++i) {
        TransformComponent t = e[i]->GetTransform();
        if (Length(t.Position() - enemy.GetTransform().Position()) <= 500) {

        }
    }*/
    return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Rule3(Level::Entities& e, Entity& enemy) {
    /*for (int i = 0; i < e.size(); ++i) {
        TransformComponent t = e[i]->GetTransform();
        if (Length(t.Position() - enemy.GetTransform().Position()) <= 500) {

        }
    }*/
    return sf::Vector2f(0.0f, 0.0f);
}


void BoidsState::Update(Enemy & enemy, sf::RenderWindow & window, double delta, const Level & level) {
    auto e = level.GetEntities();
    auto v1 = Rule1(e, enemy);
    auto v2 = Rule2(e, enemy);
    auto v3 = Rule3(e, enemy);

    enemy.SetPosition(enemy.GetTransform().Position() + (v1 + v2 + v3) * (float)delta);
}

void BoidsState::Enter(Enemy & enemy) {
}
