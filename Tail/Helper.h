#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <random>
#include <SFML\Graphics.hpp>

#define PI (3.141592653589793)


inline float Dot(const sf::Vector2f a, const sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

inline sf::Vector3f Cross(const sf::Vector3f a, const sf::Vector3f b) {
    return sf::Vector3f(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

inline sf::Vector3f Cross(const sf::Vector2f a, const sf::Vector2f b) {
    return sf::Vector3f(a.y*1 - 1*b.y, 1*b.x - a.x*1, a.x*b.y - a.y*b.x);
}

inline float Length(sf::Vector2f vector)
{
    return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

inline float Length(sf::Vector3f vector) {
    return std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

inline void Normalize(sf::Vector2f& vector)
{
    float length = Length(vector);
    if(length != 0)
    {
        vector.x = vector.x/float(length);
        vector.y = vector.y/float(length);
    }
}

inline float RotationDeg2D(const sf::Vector2f& from, const sf::Vector2f to)
{
    float dx = to.x - from.x;
    float dy = to.y - from.y;

    sf::Vector2f up(0.0f, -1.0f);

    float angle_a = std::atan2(up.y, up.x);
    float angle_b = std::atan2(dy, dx);

    float radian_aTob = angle_b - angle_a;

    float degree = float(radian_aTob * (180/PI));
    if(degree < 0)
        degree += 360;

    return degree;
}

inline float RotationRad2D(sf::Vector2f from, sf::Vector2f to)
{
    float dx = to.x - from.x;
    float dy = to.y - from.y;

    sf::Vector2f up(0.0f, -1.0f);

    float angle_a = std::atan2(up.y, up.x);
    float angle_b = std::atan2(dy, dx);

    float radian_aTob = angle_b - angle_a;
    return radian_aTob;
}

inline float Random(float a, float b)
{
    std::random_device randomDevice;
    std::mt19937 marsenneTwister(randomDevice());
    std::uniform_real_distribution<> dist(a, b);

    return (float)dist(marsenneTwister);
}

inline int Max(int a, int b) {
    return a > b ? a : b;
}

inline int Min(int a, int b) {
    return a < b ? a : b;
}

inline int Clamp(int v, int min, int max) {
    return Max(min, Min(v, max));
}

#endif