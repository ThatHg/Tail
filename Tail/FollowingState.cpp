#include "FollowingState.h"
#include "Entity.h"
#include "Helper.h"
#include "IdlingState.h"
#include "Level.h"
#include "Components\BreedComponent.h"

EnemyState* FollowingState::HandleCommand(Command command) {
    if (command == Command::IDLE) {
        return new IdlingState();
    }
    return NULL;
}

void FollowingState::Update(Entity & enemy, sf::RenderWindow& window, float delta, const Level&) {
    auto rectTransform = enemy.RectTransform();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f target((float)mousePosition.x, (float)mousePosition.y);
    sf::Vector2f position = rectTransform.getPosition();

    //enemy.SetTarget(target);

    float rotation = RotationDeg2D(position, target);
    if (rotation >= 360 || rotation < 0)
        rotation = 0;

    rectTransform.setRotation(rotation + Random(-4, 4));

    sf::Vector2f lookAt = target - position;
    Normalize(lookAt);

    const auto breed = enemy.GetComponent<BreedComponent>();

    float speed = breed->Speed();

    sf::Vector2f newPosition = lookAt * speed * delta * 10.0f;

    rectTransform.setPosition(position + newPosition);
}

void FollowingState::Enter(Entity &) {
}
