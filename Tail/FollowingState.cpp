#include "FollowingState.h"
#include "Enemy.h"
#include "Helper.h"
#include "IdlingState.h"
#include "Level.h"

EnemyState* FollowingState::HandleCommand(Command command) {
    if (command == Command::IDLE) {
        return new IdlingState();
    }
    return NULL;
}

void FollowingState::Update(Enemy & enemy, sf::RenderWindow& window, double delta, const Level& level) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f target((float)mousePosition.x, (float)mousePosition.y);
    sf::Vector2f position = enemy.GetPosition();

    enemy.SetTarget(target);

    double rotation = RotationDeg2D(enemy.GetPosition(), enemy.GetTarget());
    if (rotation >= 360 || rotation < 0)
        rotation = 0;

    enemy.SetRotation((float)rotation + (float)Random(-4, 4));

    sf::Vector2f lookAt = target - position;// +sf::Vector2f((float)Random(-1, 1), (float)Random(-1, 1));
    Normalize(lookAt);
    enemy.SetLookAt(lookAt);

    double speed = enemy.GetWalkingSpeed();

    sf::Vector2f newPosition = lookAt * (float)(speed * delta) * 10.0f;

    enemy.SetPosition(position + newPosition);
}

void FollowingState::Enter(Enemy & enemy) {
    enemy.SetSprite(enemy.GetFollowingSprite());
}
