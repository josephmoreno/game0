#pragma once

#include "../Vector2d.hpp"

class Acceleration final {
private:
    Vector2d accel;
    int scale = 1;

public:
    Acceleration() { accel.zero(); }
    Acceleration(int scale) { this->scale = scale; };
    Acceleration(float x, float y) { accel.x = x; accel.y = y; };

    Vector2d getAccel() { return accel; };
    Vector2d getAccelScaled() { Vector2d temp(accel.x, accel.y); return (temp * Vector2d(scale, scale)); };
    Vector2d& getAccelRef() { return accel; };

    bool isZero() { return (accel.x == 0 && accel.y == 0); }
};