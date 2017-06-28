#ifndef SFML_CLOCK_WRAPPER_H
#define SFML_CLOCK_WRAPPER_H

#include <SFML\System\Clock.hpp>
#include "Clock.h"

class SFMLClockWrapper : public Clock {
public:
    virtual double Time() {
        return m_clock.getElapsedTime().asSeconds();
    }
private:
    sf::Clock m_clock;
};

#endif
