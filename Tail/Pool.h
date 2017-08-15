#ifndef POOL_H
#define POOL_H

#include <cassert>
#include <vector>
#include "Particle.h"

class Pool {
public:
    Pool();
    Pool(int size);
    ~Pool();
    Particle& ActivateNext();
    void Deactivate(int index);
    int NumActive() const;
    size_t Size();
    void Reset();

    inline Particle& operator[] (int idx) {
        assert(idx > -1 && idx < Size());
        return m_elements[idx];
    }

private:
    const static int DEFAULT_SIZE = 1000;

    void Add(int index);
    void Remove(int index);

    std::vector<Particle> m_elements;
    int m_numActive;
};

#endif // !POOL_H