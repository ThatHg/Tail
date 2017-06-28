#include "GameTime.h"
#include "Clock.h"

GameTime::GameTime(double stepSize, Clock* clock):
    m_accumulator(0.0),
    m_alpha(0.0),
    m_simulatedTime(0.0),
    m_currentTime(0.0),
    m_stepSize(stepSize),
    m_clock(clock){
}

GameTime::~GameTime() {
    delete m_clock;
}

bool GameTime::StepForward() {
    if (m_accumulator >= m_stepSize) {
        m_simulatedTime += m_stepSize;
        m_accumulator -= m_stepSize;
        return true;
    }
    else {
        m_alpha = m_accumulator / m_stepSize;
        return false;
    }
}

double GameTime::DeltaTime() {
    return m_stepSize;
}

double GameTime::BlendFactor() {
    return m_alpha;
}

void GameTime::Accumulate() {
    double newTime = m_clock->Time();
    double delta = newTime - m_currentTime;
    // Prevent simulated system to blow up
    // by restricting delta size
    if (delta > 0.25) {
        delta = 0.25;
    }
    m_accumulator += delta;
}
