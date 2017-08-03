#include "BoidsState.h"
#include "IdlingState.h"
#include "Enemy.h"
#include "Helper.h"
#include "Components\PhysicsComponent.h"

BoidsState::BoidsState(float distance) :
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
    auto t2 = enemy.RectTransform();
    for (size_t i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            auto t = e[i]->RectTransform();
            if (Length(t.getPosition() - t2.getPosition()) <= m_distance) {
                center_of_mass += t.getPosition();
                flock_size++;
            }
        }
    }
    float inverse = flock_size == 0 ? 1.0f : 1.0f / (float)flock_size;
    center_of_mass *= inverse;

    return ( center_of_mass - enemy.RectTransform().getPosition()) * 0.01f;
}

sf::Vector2f BoidsState::Rule2(Level::Entities& e, Entity& enemy) {
    sf::Vector2f displacement(0.0f, 0.0f);
    auto t2 = enemy.RectTransform();
    for (size_t i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            auto t = e[i]->RectTransform();
            if (Length(t.getPosition() - t2.getPosition()) < 32) {
                displacement = displacement - (t.getPosition() - t2.getPosition());
            }
        }
    }
    return displacement;
}

sf::Vector2f BoidsState::Rule3(Level::Entities& e, Entity& enemy, PhysicsComponent* pc) {
    sf::Vector2f velocity(0.0f, 0.0f);
    int flock_size = 0;
    auto t2 = enemy.RectTransform();
    for (size_t i = 0; i < e.size(); ++i) {
        if (e[i] != &enemy) {
            auto t = e[i]->RectTransform();
            auto physics = e[i]->GetComponent<PhysicsComponent>();
            if (Length(t.getPosition() - t2.getPosition()) <= m_distance) {
                velocity += physics->Velocity();
                flock_size++;
            }
        }
    }
    float inverse = flock_size == 0 ? 1.0f : 1.0f / (float)flock_size;
    velocity *= inverse;
    return (velocity - pc->Velocity()) * 0.1f;
}

sf::Vector2f BoidsState::Rule4(Enemy & enemy, sf::RenderWindow & window) {
    auto pos = enemy.RectTransform().getPosition();
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

sf::Vector2f BoidsState::Rule5(Enemy & enemy, const Level & level) {
    const auto player = level.GetPlayer();
    auto player_dir = player->RectTransform().getPosition() - enemy.RectTransform().getPosition();
    float len = Length(player_dir);
    if (len < 200) {
        const auto pc = player->GetComponent<PhysicsComponent>();
        auto dot = Dot(player_dir, pc->Velocity());
        if (dot >= 0) {
            return player_dir * 0.1f;
        }
        else {
            return player_dir * -0.1f;
        }
    }
    else {
        return sf::Vector2f(0.0f, 0.0f);
    }
}

void LimitVelocity(Enemy & enemy, sf::Vector2f& v) {
    float l = Length(v);
    float inv = l == 0.0f ? 1.0f : 1.0f / l;
    if (l > enemy.GetWalkingSpeed()) {
        v = v * inv * enemy.GetWalkingSpeed();
    }
}

void BoidsState::Update(Enemy & enemy, sf::RenderWindow & window, float, const Level & level) {
    auto pc = enemy.GetComponent<PhysicsComponent>();
    auto rectTransform = enemy.RectTransform();
    auto e = level.GetEntities();
    sf::Vector2f v = pc->Velocity();

    // Apply boids rules
    v += Rule1(e, enemy);
    v += Rule2(e, enemy);
    v += Rule3(e, enemy, pc);
    v += Rule4(enemy, window);
    v += Rule5(enemy, level);
    v += sf::Vector2f(Random(-10.0f, 10.0f), Random(-10.0f, 10.0f));

    LimitVelocity(enemy, v);

    pc->AddForce(v, true);

    float rotation = RotationDeg2D(rectTransform.getPosition(), rectTransform.getPosition() + pc->Velocity());
    if (rotation >= 360 || rotation < 0)
        rotation = 0;
    
    rectTransform.setRotation(rotation);
}

void BoidsState::Enter(Enemy &) {
}
