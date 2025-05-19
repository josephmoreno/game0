#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Transform.hpp"

class Button final {
private:
    SDL_Texture* tex;
    SDL_Rect rect_src, rect_dest;
    Transform* trans = nullptr;
    bool toggle_val = false;
    void (*toggleFunc)();

public:
    Button(std::string id, Transform& trans, void (&func)()) {
        tex = Game::assets.getTex(id);
        this->trans = &trans;
        rect_src.y = 0; // Only 1 row expected on the sheet for a button, for now.
        rect_src.w = trans.w();
        rect_src.h = trans.h();

        rect_dest.x = trans.getPos().x;
        rect_dest.y = trans.getPos().y;
        rect_dest.w = trans.w() * trans.sc();
        rect_dest.h = trans.h() * trans.sc();

        toggleFunc = &func;
    };

    ~Button() {};

    void toggleBtn() {
        toggle_val = !toggle_val;
        toggleFunc();
    };

    void update() {
        rect_src.x = rect_src.w * (toggle_val ? 1 : 0);
    };

    void draw() {
        Game::assets.drawTex(tex, rect_src, rect_dest, SDL_FLIP_NONE);
    };
};