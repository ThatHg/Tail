#ifndef INPUT_BASE_H
#define INPUT_BASE_H

class Entity;

class InputBase {
public:
    virtual ~InputBase() {}
    virtual void Update(Entity& entity, double delta) = 0;
};

#endif