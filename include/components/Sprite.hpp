#pragma once

#include <map>
#include <tuple>
#include <string>
#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Transform.hpp"

class Sprite final {
private:
    SDL_Texture* tex;
    SDL_Rect rect_src, rect_dest;

    Transform* transform = nullptr;
    bool animated = false;
    int frames = 0;
    int speed = 100;    // Delay between frames in ms
    int ss_row;         // Row on the sprite sheet to use for the animation

public:
    std::map<std::string, std::tuple<std::string, int, int, int>> animations;   // <descriptive name for animation, <texture key for asset manager, ss_row, # of frames, speed>>

    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

    Sprite() {};
    Sprite(std::string tex_key, Transform& transform) {  // Construct still sprite
        this->transform = &transform;
        setTex(tex_key);

        if (this->transform != nullptr) {
            rect_src.x = rect_src.y = 0;
            rect_src.w = this->transform->w();
            rect_src.h = this->transform->h();
        }
    };

    Sprite(std::string anim_name, std::string tex_key, int ss_row, int frames, int speed, Transform& transform) {  // Construct animated sprite
        animated = true;
        this->frames = frames;
        this->speed = speed;
        setTex(tex_key);
        this->transform = &transform;
        
        std::tuple<std::string, int, int, int> anim_data(tex_key, ss_row, frames, speed);
        animations.emplace(anim_name, anim_data);

        if (this->transform != nullptr) {
            rect_src.x = rect_src.y = 0;
            rect_src.w = this->transform->w();
            rect_src.h = this->transform->h();
        }

        // play("Idle");
    };

    ~Sprite() {
        // SDL_DestroyTexture(tex);
    };

    void setTex(std::string tex_id) {
        tex = Game::assets.getTex(tex_id);
    };

    // void init() {
    //     // transform = &entity->getComponent<TransformComponent>();

    //     rect_src.x = rect_src.y = 0;
    //     // rect_src.w = transform->width;
    //     // rect_src.h = transform->height;

    //     rect_src.w = 32;
    //     rect_src.h = 32;
    // };

    void update() {
        if (animated)
            rect_src.x = rect_src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        if (transform != nullptr) {
            rect_src.y = ss_row * transform->h();

            // rect_dest.x = static_cast<int>(transform->getPos().x) - Game::camera.x;
            // rect_dest.y = static_cast<int>(transform->getPos().y) - Game::camera.y;
            rect_dest.w = transform->w() * transform->sc();
            rect_dest.h = transform->h() * transform->sc();
        }
    };

    void draw() {
        Game::assets.drawTex(tex, rect_src, rect_dest, sprite_flip);
    };

    void play(const char* anim_name) {
        ss_row = std::get<1>(animations[anim_name]);
        frames = std::get<2>(animations[anim_name]);
        speed = std::get<3>(animations[anim_name]);
    };
};