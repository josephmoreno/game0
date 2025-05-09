#pragma once

#include "../Vector2d.hpp"

class Velocity final {
private:
    Vector2d vel;

public:
    Velocity() { vel.zero(); };
    Velocity(float x, float y) { vel.x = x; vel.y = y; };

    Vector2d getVel() { return vel; };
    Vector2d& getVelRef() { return vel; };
};