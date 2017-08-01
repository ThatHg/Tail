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

void IdlingState::Update(Enemy & enemy, sf::RenderWindow&, float, const Level&) {
    enemy.SetRotation(6);
}

void IdlingState::Enter(Enemy & enemy) {
    enemy.SetSprite(enemy.GetFollowingSprite());
    m_idlingTimer = 0;
}
