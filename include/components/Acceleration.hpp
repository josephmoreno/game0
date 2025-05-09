#pragma once

#include "../Vector2d.hpp"

class Acceleration final {
private:
    Vector2d accel;

public:
    Acceleration() { accel.zero(); }
    Acceleration(float x, float y) { accel.x = x; accel.y = y; };

    Vector2d getAccel() { return accel; };
    Vector2d& getAccelRef() { return accel; };
};