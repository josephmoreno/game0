#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Transform.hpp"

class Tile final {
private:
    Transform* trans = nullptr;
    SDL_Texture* tex;
    SDL_Rect rect_src, rect_dest;

public:
    Tile(int src_x, int src_y, std::string tex_id, Transform& trans) {
        tex = Game::assets.getTex(tex_id);
        this->trans = &trans;

        rect_src.x = src_x;
        rect_src.y = src_y;
        rect_src.w = rect_src.h = this->trans->w();

        rect_dest.x = static_cast<int>(this->trans->getPos().x);
        rect_dest.y = static_cast<int>(this->trans->getPos().y);
        rect_dest.w = rect_dest.h = this->trans->w() * this->trans->sc();
    };

    void update() {
        rect_dest.x = static_cast<int>(this->trans->getPos().x) - Game::camera.x;
        rect_dest.y = static_cast<int>(this->trans->getPos().y) - Game::camera.y;
    };

    void draw() {
        Game::assets.drawTex(tex, rect_src, rect_dest, SDL_FLIP_NONE);
    };

    ~Tile() {};
};