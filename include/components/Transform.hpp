#pragma once

#include "../Vector2d.hpp"
#include "Velocity.hpp"

// Entity's on-screen position and dimensions
class Transform final {
private:
    Vector2d pos;

    int width = 32;
    int height = 32;
    int scale = 1;

public:
    Transform() {
        pos.zero();
    };

    Transform(int sc) {
        pos.zero();
        scale = sc;
    };

    Transform(float x, float y) {
        pos.x = x;
        pos.y = y;
    };

    Transform(int w, int h, int sc) {
        pos.zero();
        width = w;
        height = h;
        scale = sc;
    };

    Transform(float x, float y, int w, int h, int sc) {
        pos.x = x;
        pos.y = y;
        width = w;
        height = h;
        scale = sc;
    };

    Vector2d getPos() { return pos; };
    Vector2d& getPosRef() { return pos; };
    
    void setTransform(float x, float y, int width, int height, int scale) {
        pos = Vector2d(x, y);
        this->width = width;
        this->height = height;
        this->scale = scale;
    };
    
    int w() { return width; };
    int h() { return height; };
    int sc() { return scale; };
};