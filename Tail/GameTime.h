#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <SFML\Graphics.hpp>

// Based on the article "Fix your timestep" by Glenn Fiedler

class GameTime {
public:
    GameTime(double stepSize);
    ~GameTime();
    bool StepForward();             // Will step through divided accumulated time, nessesary when doing physics calculation. returns true when stepping is finished.
    double DeltaTime();             // Time since last frame
    double BlendFactor();           // Remaining fractional part of stepSize that were too small for StepForward to simulate/handle. 

    void Accumulate();              // Accumulate time which will then be divided into stepSized chunks by StepForward
private:
    double m_accumulator;           // Accumulated time since last frame.
    double m_alpha;
    double m_simulatedTime;
    double m_currentTime;
    const double m_stepSize;        // Step size which will divide accumulated time into chunks.
    sf::Clock m_clock;
};

#endif

