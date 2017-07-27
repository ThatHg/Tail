#include "Player.h"
#include "InputBase.h"

Player::Player(InputBase* input) :
    _input(input){
    this->SetSprite("player.png");
}

Player::~Player() {
    delete _input;
}

void Player::Update(sf::RenderWindow & window, double delta) {
    _input->Update(*this, delta);
}
