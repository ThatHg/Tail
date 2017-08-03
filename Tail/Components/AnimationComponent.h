#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <SFML\Graphics.hpp>
#include <string>
#include "../GameTime.h"
#include "Component.h"

enum PlaybackType {
    InvalidType = -1,
    One = 0,
    Loop,
    Bounce,
    PlaybackTypeCount
};

struct AnimationSheetInfo {
    int m_width;
    int m_height;
    int m_count;
    float m_duration;
    PlaybackType m_playback_type;
    std::string m_name;
};

class AnimationComponent : public Component {
public:
    AnimationComponent();
    void Init(const AnimationSheetInfo& info);
    virtual void Update();
    virtual void FixedUpdate(sf::RenderWindow& window, float delta, const Level& level);
private:
    void Next();
    void ChangeFrame();
    AnimationSheetInfo m_sheet_info;
    GameTime m_time;
    int m_current_frame;
    int m_play_direction;
    bool m_dirty;
    bool m_initialized;
};

#endif
