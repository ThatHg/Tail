#include "GameTime.h"
#include "Clock.h"
#include <cassert>

GameTime::GameTime(Clock* clock) :
    m_accumulator(0.0),
    m_alpha(0.0),
    m_simulatedTime(0.0),
    m_currentTime(0.0),
    m_stepSize(-1.0),
    m_clock(clock){
}

GameTime::GameTime(double stepSize, Clock* clock) :
    m_accumulator(0.0),
    m_alpha(0.0),
    m_simulatedTime(0.0),
    m_currentTime(0.0),
    m_stepSize(stepSize),
    m_clock(clock) {
#ifndef _DEBUG
    assert(m_stepSize > 0 && "Stepsize must be greater than 0");
#endif // !_DEBUG
}

GameTime::~GameTime() {
    delete m_clock;
}

bool GameTime::StepForward() {
    if (m_accumulator >= m_stepSize && m_stepSize > 0) {
        m_simulatedTime += m_stepSize;
        m_accumulator -= m_stepSize;
        return true;
    }
    else {
        m_alpha = m_accumulator / m_stepSize;
        return false;
    }
}

double GameTime::StepSize() {
    return m_stepSize;
}

double GameTime::DeltaTime() {
    double newTime = m_clock->Time();
    return newTime - m_currentTime;
}

double GameTime::BlendFactor() {
    return m_alpha;
}

void GameTime::SetStepSize(double step) {
#ifndef _DEBUG
    assert(step > 0 && "Stepsize must be greater than 0");
#endif
    m_stepSize = step;
}

void GameTime::Accumulate() {
    double delta = DeltaTime();
    // Prevent simulated system to blow up
    // by restricting delta size
    if (delta > 0.25) {
        delta = 0.25;
    }
    m_accumulator += delta;
    m_currentTime = m_clock->Time();
}
