#include "AnimationComponent.h"

#include <cassert>
#include "../AssetsManager.h"
#include "../SFMLClockWrapper.h"
#include "../Helper.h"
#include "../Entity.h"
#include "GraphicsComponent.h"

AnimationComponent::AnimationComponent() :
    m_current_frame(0),
    m_time(GameTime(new SFMLClockWrapper())),
    m_play_direction(1),
    m_dirty(false) {
}

void AnimationComponent::Init(const AnimationSheetInfo& info) {
    m_sheet_info = info;
    const auto graphics = GetEntity()->GetComponent<GraphicsComponent>();
    graphics->SetTexture(AssetsManager::Ref().GetTexture(info.m_name));
    graphics->SetRect(sf::IntRect(0, 0, m_sheet_info.m_width, m_sheet_info.m_height));
    m_time.SetStepSize(info.m_duration);
    m_initialized = true;
}

void AnimationComponent::Update() {
    if (m_initialized == false) {
        return;
    }

    m_time.Accumulate();
    while (m_time.StepForward()) {
        Next();
    }
    if (m_dirty) {
        ChangeFrame();
    }
}

void AnimationComponent::FixedUpdate(sf::RenderWindow &, float, const Level &) {
}

void AnimationComponent::Next() {
    // Move to next frame in front of or behind current frame.
    m_current_frame += 1 * m_play_direction;

    switch (m_sheet_info.m_playback_type) {
    case PlaybackType::Loop: // Start from frame 0 when current frame has reached sheet frame count.
        m_current_frame = m_current_frame % m_sheet_info.m_count;
        break;
    case PlaybackType::Bounce: // Change playback direction forward or backwards.
        if (m_current_frame >= m_sheet_info.m_count) {
            m_play_direction = -1;
        }
        else if (m_current_frame < 0) {
            m_play_direction = 1;
        }
        break;
    default:
        break;
    }
    m_current_frame = Clamp(m_current_frame, 0, m_sheet_info.m_count - 1);

    // We have changed animation frame, set dirty bit.
    m_dirty = true;
}

void AnimationComponent::ChangeFrame() {
    int left_pos = m_current_frame * m_sheet_info.m_width;
    const auto graphics = GetEntity()->GetComponent<GraphicsComponent>();
    graphics->SetRect(sf::IntRect(left_pos, 0, m_sheet_info.m_width, m_sheet_info.m_height));
    m_dirty = false;
}