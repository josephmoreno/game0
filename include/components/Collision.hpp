#pragma once

#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Transform.hpp"

class Collision final {
private:
    Transform* trans = nullptr;
    SDL_Rect rect_dest;
    bool visible = false;
    Uint8 alpha = 255;

public:
    Collision(Transform& trans) { this->trans = &trans; };
    Collision(Transform& trans, bool visible) { this->trans = &trans; this->visible = visible; };
    Collision(Transform& trans, bool visible, Uint8 alpha) { this->trans = &trans; this->visible = visible; this->alpha = alpha; };

    SDL_Rect& getCollRectRef() { return rect_dest; };

    void update() {
        rect_dest.x = static_cast<int>(this->trans->getPos().x) - Game::camera.x;
        rect_dest.y = static_cast<int>(this->trans->getPos().y) - Game::camera.y;
        rect_dest.w = this->trans->w() * this->trans->sc();
        rect_dest.h = this->trans->h() * this->trans->sc();
    };

    void draw() {
        if (visible)
            Game::assets.drawAlphaRect(rect_dest, alpha);
    };
};