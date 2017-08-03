#include "Player.h"

#include <cassert>
#include <iostream>

#include "Components\PhysicsComponent.h"
#include "Components\GraphicsComponent.h"
#include "Components\PlayerInputComponent.h"
#include "Components\AnimationComponent.h"

Player::Player() {
    AddComponent<PlayerInputComponent>();
    AddComponent<GraphicsComponent>();
    const auto physics = AddComponent<PhysicsComponent>();
    physics->EnableGravity(false);
    physics->SetPosition(sf::Vector2f(300, 300));
    physics->AddForce(sf::Vector2f(15.0f, 10.0f), sf::Vector2f(364.0f, 364.0f), true);

    const auto animation = AddComponent<AnimationComponent>();
    AnimationSheetInfo info;
    info.m_count = 8;
    info.m_duration = 0.05f;
    info.m_height = 64;
    info.m_width = 64;
    info.m_playback_type = PlaybackType::Bounce;
    info.m_name = "player_open_mouth.png";
    animation->Init(info);
}

Player::~Player() {
}

void Player::Update() {
    Entity::Update();
}

void Player::FixedUpdate(sf::RenderWindow & window, float delta, const Level& level) {
    Entity::FixedUpdate(window, delta, level);
}
