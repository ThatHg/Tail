#include "Animation.h"
#include "AssetsManager.h"
#include "Helper.h"
#include "SFMLClockWrapper.h"

Animation::Animation(AnimationSheetInfo info, double frame_duration, bool looping) :
    m_current_frame(0),
    m_frame_duration(frame_duration),
    m_looping(looping),
    m_sheet_info(info),
    m_sprite(sf::Sprite(AssetsManager::Ref().GetTexture(info.m_sheet_name))),
    m_time(GameTime(frame_duration, new SFMLClockWrapper())){
    m_sprite.setTextureRect(sf::IntRect(m_current_frame, 0, m_sheet_info.m_frame_width, m_sheet_info.m_frame_height));
}

void Animation::Update() {
    m_time.Accumulate();
    while (m_time.StepForward()) {
        Next();
    }
}

void Animation::Next() {
    m_current_frame = m_looping ? (m_current_frame + 1) % m_sheet_info.m_frame_count : Min(m_current_frame + 1, m_sheet_info.m_frame_count - 1);
    int left_pos = m_current_frame * m_sheet_info.m_frame_width;
    m_sprite.setTextureRect(sf::IntRect(left_pos, 0, m_sheet_info.m_frame_width, m_sheet_info.m_frame_height));
}


