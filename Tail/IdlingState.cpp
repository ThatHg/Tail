#include "IdlingState.h"
#include "FollowingState.h"
#include "Enemy.h"

IdlingState::IdlingState() {
}

EnemyState* IdlingState::HandleCommand(Command command) {
    if (command == Command::FOLLOW) {
        return new FollowingState();
    }
    return NULL;
}

void IdlingState::Update(Enemy & enemy, sf::RenderWindow& window, double delta) {
    enemy.SetRotation(6);
}

void IdlingState::Enter(Enemy & enemy) {
    enemy.SetSprite(enemy.GetFollowingSprite());
    m_idlingTimer = 0;
}
