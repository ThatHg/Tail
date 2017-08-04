#include "EntityFactory.h"
#include "Entity.h"

#include "AssetsManager.h"
#include "Helper.h"
#include "config.h"

#include "Components\AnimationComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\GraphicsComponent.h"
#include "Components\PlayerInputComponent.h"
#include "Components\BreedComponent.h"

EntityFactory::EntityFactory() {
}

EntityFactory::~EntityFactory() {
}

Entity * EntityFactory::CreatePlayer(const std::string& breed_type) {
    const auto config = GetBreedConfig(breed_type);
    const auto entity = new Entity();

    entity->AddComponent<PlayerInputComponent>();

    const auto graphics = entity->AddComponent<GraphicsComponent>();
    graphics->SetTexture(AssetsManager::Ref().GetTexture(config->GrabString("ANIMATION_SHEET")));

    const auto physics = entity->AddComponent<PhysicsComponent>();
    physics->EnableGravity(false);
    physics->SetPosition(sf::Vector2f(
        Random(300, 1280 - 300),
        Random(300, 720 - 300)));

    const auto breed = entity->AddComponent<BreedComponent>();
    breed->SetHealth((float)config->GrabInteger("HEALTH"));
    breed->SetHealth((float)config->GrabInteger("SPEED"));

    const auto animation = entity->AddComponent<AnimationComponent>();
    AnimationSheetInfo info;
    info.m_count = config->GrabInteger("ANIMATION_FRAME_COUNT");
    info.m_duration = (float)config->GrabReal("ANIMATION_FRAME_DURATION");
    info.m_height = config->GrabInteger("ANIMATION_FRAME_HEIGHT");
    info.m_width = config->GrabInteger("ANIMATION_FRAME_WIDTH");
    info.m_playback_type = (PlaybackType)config->GrabInteger("ANIMATION_PLAYBACK_TYPE");
    info.m_name = config->GrabString("ANIMATION_SHEET");
    animation->Init(info);

    return entity;
}

Entity * EntityFactory::CreateEnemy(const std::string& breed_type) {
    const auto config = GetBreedConfig(breed_type);
    const auto entity = new Entity();

    const auto graphics = entity->AddComponent<GraphicsComponent>();
    graphics->SetTexture(AssetsManager::Ref().GetTexture(config->GrabString("ANIMATION_SHEET")));

    const auto physics = entity->AddComponent<PhysicsComponent>();
    physics->EnableGravity(false);
    physics->SetPosition(sf::Vector2f(
        Random(64, 1280 - 64),
        Random(64, 720 - 64)));

    const auto breed = entity->AddComponent<BreedComponent>();
    breed->SetHealth((float)config->GrabInteger("HEALTH"));
    breed->SetHealth((float)config->GrabInteger("SPEED"));

    const auto animation = entity->AddComponent<AnimationComponent>();
    AnimationSheetInfo info;
    info.m_count = config->GrabInteger("ANIMATION_FRAME_COUNT");
    info.m_duration = (float)config->GrabReal("ANIMATION_FRAME_DURATION");
    info.m_height = config->GrabInteger("ANIMATION_FRAME_HEIGHT");
    info.m_width = config->GrabInteger("ANIMATION_FRAME_WIDTH");
    info.m_playback_type = (PlaybackType)config->GrabInteger("ANIMATION_PLAYBACK_TYPE");
    info.m_name = config->GrabString("ANIMATION_SHEET");
    animation->Init(info);

    return entity;
}

const Config* EntityFactory::GetBreedConfig(const std::string& breed_type) {
    const auto itr = m_breeds.find(breed_type);
    if (itr != m_breeds.end()) {
        return itr->second;
    }
    else {
        m_breeds[breed_type] = new Config(breed_type);
        return m_breeds[breed_type];
    }
}

