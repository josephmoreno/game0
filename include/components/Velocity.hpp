#pragma once

#include "../Vector2d.hpp"

class Velocity final {
private:
    Vector2d vel;
    int scale = 1;

public:
    Velocity() { vel.zero(); };
    Velocity(int scale) { this->scale = scale; };
    Velocity(float x, float y) { vel.x = x; vel.y = y; };

    Vector2d getVel() { return vel; };
    Vector2d getVelScaled() { Vector2d temp(vel.x, vel.y); return (temp * Vector2d(scale, scale)); };
    Vector2d& getVelRef() { return vel; };
};