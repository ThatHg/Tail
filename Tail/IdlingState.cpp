#include "IdlingState.h"
#include "FollowingState.h"
#include "Entity.h"
#include "Level.h"

IdlingState::IdlingState() {
}

EnemyState* IdlingState::HandleCommand(Command command) {
    if (command == Command::FOLLOW) {
        return new FollowingState();
    }
    if (command == Command::BOIDS) {
        return new FollowingState();
    }
    return NULL;
}

void IdlingState::Update(Entity & enemy, sf::RenderWindow&, float delta, const Level&) {
    enemy.RectTransform().rotate(10 * delta);
}

void IdlingState::Enter(Entity &) {
    m_idlingTimer = 0;
}
