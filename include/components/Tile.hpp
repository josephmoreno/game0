#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Transform.hpp"

class Tile final {
private:
    Transform* transform = nullptr;
    SDL_Texture* tex;
    SDL_Rect rect_src, rect_dest;

public:
    Tile(int src_x, int src_y, std::string tex_id, Transform& transform) {
        tex = Game::assets.getTex(tex_id);
        this->transform = &transform;

        rect_src.x = src_x;
        rect_src.y = src_y;
        rect_src.w = rect_src.h = this->transform->w();

        rect_dest.x = this->transform->getPos().x;
        rect_dest.y = this->transform->getPos().y;
        rect_dest.w = rect_dest.h = this->transform->w() * this->transform->sc();
    };

    void update() {
        rect_dest.x = this->transform->getPos().x - Game::camera.x;
        rect_dest.y = this->transform->getPos().y - Game::camera.y;
    };

    void draw() {
        Game::assets.drawTex(tex, rect_src, rect_dest, SDL_FLIP_NONE);
    };

    ~Tile() {};
};