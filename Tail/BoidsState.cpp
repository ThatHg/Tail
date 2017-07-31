#include "BoidsState.h"
#include "IdlingState.h"

EnemyState * BoidsState::HandleCommand(Command command) {
    if (command == Command::IDLE) {
        return new IdlingState();
    }
    return NULL;
}

void BoidsState::Update(Enemy & enemy, sf::RenderWindow & window, double delta, const Level & level) {
}

void BoidsState::Enter(Enemy & enemy) {
}
