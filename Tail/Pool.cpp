#include "Pool.h"
#include <utility>

Pool::Pool() {
    m_numActive = 0;
    m_elements.resize(DEFAULT_SIZE);
}

Pool::Pool(int size) {
    m_numActive = 0;
    m_elements.resize(size);
}

Pool::~Pool() {
}

Particle & Pool::ActivateNext() {
    if (m_numActive < Size()) {
        Add(m_numActive);
    }
    return m_elements[m_numActive - 1];
}

void Pool::Deactivate(int index) {
    Remove(index);
}

int Pool::NumActive() const {
    return m_numActive;
}

size_t Pool::Size() {
    return m_elements.size();
}

void Pool::Reset() {
    m_numActive = 0;
}

void Pool::Add(int index) {
    // Shouldn't already be active!
    assert(index >= m_numActive);

    if (m_elements.size() == index) {
        m_elements.push_back(Particle());
    }

    // Swap it with the first inactive
    // right after the active ones.
    //std::swap(m_elements[m_numActive], m_elements[index]);
    Particle temp = m_elements[m_numActive];
    m_elements[m_numActive] = m_elements[index];
    m_elements[index] = temp;

    // Now there's one more.
    m_numActive++;
}
void Pool::Remove(int index) {
    // Shouldn't already be inactive!
    assert(index < m_numActive);

    // There's one fewer.
    m_numActive--;

    // Swap it with the last active
    // right before the inactive ones.
    //std::swap(m_elements[m_numActive], m_elements[index]);
    Particle temp = m_elements[m_numActive];
    m_elements[m_numActive] = m_elements[index];
    m_elements[index] = temp;
}