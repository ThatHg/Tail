#include "Player.h"
#include "InputBase.h"
#include "Animation.h"

Player::Player(InputBase* input) :
    _input(input){
    this->SetSprite("player.png");

    AnimationSheetInfo info;
    info.m_frame_count = 8;
    info.m_frame_height = 64;
    info.m_frame_width = 64;
    info.m_sheet_name = "player_open_mouth.png";
    m_animation = new Animation(info, 0.04, PlaybackType::Bounce);
}

Player::~Player() {
    delete _input;
    delete m_animation;
}

void Player::Update() {
    m_animation->Update();
}

void Player::FixedUpdate(sf::RenderWindow & window, double delta, const Level& level) {
    _input->Update(*this, delta);
}
