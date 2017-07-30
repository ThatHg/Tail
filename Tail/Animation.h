#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>
#include <string>
#include "GameTime.h"

struct AnimationSheetInfo {
    int m_frame_width;
    int m_frame_height;
    int m_frame_count;
    std::string m_sheet_name;
};

class Animation {
public:
    Animation(AnimationSheetInfo info, double frame_duration, bool looping);
    void Update();
    sf::Sprite& GetCurrentFrame() { return m_sprite; }
    void SetPosition(const sf::Vector2f& position) { m_sprite.setPosition(position); };
private:
    void Next();

    int m_current_frame;
    double m_frame_duration;
    bool m_looping;
    AnimationSheetInfo m_sheet_info;
    sf::Sprite m_sprite;
    GameTime m_time;
};

#endif
