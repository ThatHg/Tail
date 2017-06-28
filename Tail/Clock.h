#ifndef CLOCK_H
#define CLOCK_H

class Clock {
public:
    virtual ~Clock() {};
    virtual double Time() = 0;
};

#endif