#pragma once

#include <iostream>

class Vector2d {
public:
    float x;
    float y;

    Vector2d();
    Vector2d(float x, float y);

    Vector2d& add(const Vector2d& v);
    Vector2d& subtract(const Vector2d& v);
    Vector2d& multiply(const Vector2d& v);
    Vector2d& divide(const Vector2d& v);

    friend Vector2d& operator+(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator-(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator*(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator/(Vector2d& v1, const Vector2d& v2);

    Vector2d& operator+=(const Vector2d& v);
    Vector2d& operator-=(const Vector2d& v);
    Vector2d& operator*=(const Vector2d& v);
    Vector2d& operator/=(const Vector2d& v);

    Vector2d& operator*(const int& i);
    Vector2d& zero();

    friend std::ostream& operator<<(std::ostream& stream, const Vector2d& v);
};