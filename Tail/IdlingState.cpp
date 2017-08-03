#include "IdlingState.h"
#include "FollowingState.h"
#include "Enemy.h"
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

void IdlingState::Update(Enemy & enemy, sf::RenderWindow&, float delta, const Level&) {
    enemy.RectTransform().rotate(10 * delta);
}

void IdlingState::Enter(Enemy &) {
    m_idlingTimer = 0;
}
