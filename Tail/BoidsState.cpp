#include "BoidsState.h"
#include "IdlingState.h"
#include "Enemy.h"
#include "TransformComponent.h"
#include "Helper.h"

BoidsState::BoidsState(double distance) :
m_distance(distance){

}

EnemyState * BoidsState::HandleCommand(Command command) {
    if (command == Command::IDLE) {
        return new IdlingState();
    }
    return NULL;
}

sf::Vector2f BoidsState::Rule1(Level::Entities& e, Entity& enemy) {
    sf::Vector2f center_of_mass(0.0f, 0.0f);
    int flock_size = 0;
    for (int i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            TransformComponent t = e[i]->GetTransform();
            if (Length(t.Position() - enemy.GetTransform().Position()) <= m_distance) {
                center_of_mass += t.Position();
                flock_size++;
            }
        }
    }
    float inverse = flock_size == 0 ? 1.0f : 1.0f / (float)flock_size;
    center_of_mass *= inverse;

    return ( center_of_mass - enemy.GetTransform().Position()) * 0.01f;
}

sf::Vector2f BoidsState::Rule2(Level::Entities& e, Entity& enemy) {
    sf::Vector2f displacement(0.0f, 0.0f);
    for (int i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            TransformComponent t = e[i]->GetTransform();
            if (Length(t.Position() - enemy.GetTransform().Position()) < 32) {
                displacement = displacement - (t.Position() - enemy.GetTransform().Position());
            }
        }
    }
    return displacement;
}

sf::Vector2f BoidsState::Rule3(Level::Entities& e, Entity& enemy) {
    sf::Vector2f velocity(0.0f, 0.0f);
    int flock_size = 0;
    for (int i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            TransformComponent t = e[i]->GetTransform();
            if (Length(t.Position() - enemy.GetTransform().Position()) <= m_distance) {
                velocity += t.Velocity();
                flock_size++;
            }
        }
    }
    float inverse = flock_size == 0 ? 1.0f : 1.0f / (float)flock_size;
    velocity *= inverse;
    return (velocity - enemy.GetTransform().Velocity()) * 0.1f;
}

sf::Vector2f BoidsState::Rule4(Enemy & enemy, sf::RenderWindow & window) {
    auto pos = enemy.GetTransform().Position();
    sf::Vector2f v(0.0f, 0.0f);
    if (pos.x < 0) {
        v.x = 1;
    }
    else if (pos.x > window.getSize().x) {
        v.x = -1;
    }
    if (pos.y < 0) {
        v.y = 1;
    }
    else if (pos.y > window.getSize().y) {
        v.y = -1;
    }
    float encouragement = 10.0f;
    return v * encouragement;
}

void LimitVelocity(sf::Vector2f& v) {
    double l = Length(v);
    float inv = (float)(l == 0.0 ? 1 : 1.0 / l);
    if (l > 100.0f) {
        v = (v * inv) * 100.0f;
    }
}

void BoidsState::Update(Enemy & enemy, sf::RenderWindow & window, double delta, const Level & level) {
    auto e = level.GetEntities();
    auto v1 = Rule1(e, enemy);
    auto v2 = Rule2(e, enemy);
    auto v3 = Rule3(e, enemy);
    auto v4 = Rule4(enemy, window);

    auto v = enemy.GetTransform().Velocity() + v1 + v2 + v3 + v4;

    LimitVelocity(v);

    enemy.SetVelocity(v);
    enemy.SetPosition(enemy.GetTransform().Position() + enemy.GetTransform().Velocity() * (float)delta);
    double rotation = RotationDeg2D(enemy.GetTransform().Position(), enemy.GetTransform().Position() + enemy.GetTransform().Velocity());
    if (rotation >= 360 || rotation < 0)
        rotation = 0;

    enemy.SetRotation((float)rotation);
}

void BoidsState::Enter(Enemy & enemy) {
}
