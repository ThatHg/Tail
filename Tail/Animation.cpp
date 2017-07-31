#include "Animation.h"
#include "AssetsManager.h"
#include "Helper.h"
#include "SFMLClockWrapper.h"

Animation::Animation(AnimationSheetInfo info, double frame_duration, PlaybackType playback_type) :
    m_current_frame(0),
    m_frame_duration(frame_duration),
    m_playback_type(playback_type),
    m_sheet_info(info),
    m_sprite(sf::Sprite(AssetsManager::Ref().GetTexture(info.m_sheet_name))),
    m_time(GameTime(frame_duration, new SFMLClockWrapper())),
    m_play_direction(1){
    m_sprite.setTextureRect(sf::IntRect(m_current_frame, 0, m_sheet_info.m_frame_width, m_sheet_info.m_frame_height));
}

void Animation::Update() {
    m_time.Accumulate();
    while (m_time.StepForward()) {
        Next();
    }
}

void Animation::Next() {
    // Move to next frame in front of or behind current frame.
    m_current_frame += 1 * m_play_direction;

    switch (m_playback_type) {
    case PlaybackType::Loop: // Start from frame 0 when current frame has reached sheet frame count.
        m_current_frame = m_current_frame % m_sheet_info.m_frame_count;
        break;
    case PlaybackType::Bounce: // Change playback direction forward or backwards.
        if (m_current_frame >= m_sheet_info.m_frame_count) {
            m_play_direction = -1;
        }
        else if (m_current_frame < 0) {
            m_play_direction = 1;
        }
        break;
    default:
        break;
    }
    m_current_frame = Clamp(m_current_frame, 0, m_sheet_info.m_frame_count - 1);
    int left_pos = m_current_frame * m_sheet_info.m_frame_width;
    m_sprite.setTextureRect(sf::IntRect(left_pos, 0, m_sheet_info.m_frame_width, m_sheet_info.m_frame_height));
}


