#pragma once

#include <map>
#include <tuple>
#include <string>
#include <SDL2/SDL.h>

#include "../Game.hpp"
#include "Vector2d.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "Acceleration.hpp"

class Sprite final {
private:
    SDL_Texture* tex;
    SDL_Rect rect_src, rect_dest;
    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

    bool animated = false;
    int frames = 0;
    int speed = 100;    // Delay between frames in ms
    int ss_row;         // Row on the sprite sheet to use for the animation

    float temp = 0;

public:
    Transform* transform = nullptr;
    Velocity* vel = nullptr;
    Acceleration* accel = nullptr;
    std::map<std::string, std::tuple<std::string, int, int, int>> animations;   // <descriptive name for animation, <texture key for asset manager, ss_row, # of frames, speed>

    Sprite() {};
    Sprite(std::string tex_key, Transform& transform) {  // Construct un-animated sprite
        this->transform = &transform;
        setTex(tex_key);

        if (this->transform != nullptr) {
            rect_src.x = rect_src.y = 0;
            rect_src.w = this->transform->w();
            rect_src.h = this->transform->h();
        }
    };

    Sprite(std::string anim_name, std::string tex_key, int ss_row, int frames, int speed, Transform& transform) {  // Construct animated sprite
        this->transform = &transform;

        if (this->transform != nullptr) {
            rect_src.x = rect_src.y = 0;
            rect_src.w = this->transform->w();
            rect_src.h = this->transform->h();
        }

        addAnim(anim_name, tex_key, ss_row, frames, speed);

        setCurAnim(anim_name);
    };

    Sprite(std::string anim_name, std::string tex_key, int ss_row, int frames, int speed, Transform& transform, Velocity& vel, Acceleration& accel) {  // Construct animated sprite with velocity and acceleration
        this->transform = &transform;
        this->vel = &vel;
        this->accel = &accel;

        if (this->transform != nullptr) {
            rect_src.x = rect_src.y = 0;
            rect_src.w = this->transform->w();
            rect_src.h = this->transform->h();
        }

        addAnim(anim_name, tex_key, ss_row, frames, speed);

        setCurAnim(anim_name);
    };

    ~Sprite() {};

    void setTex(std::string tex_id) {
        tex = Game::assets.getTex(tex_id);
    };

    void update() {
        if (animated)
            rect_src.x = rect_src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        if (transform != nullptr) {
            rect_src.y = ss_row * transform->h();

            // rect_dest.x = static_cast<int>(transform->getPos().x) - Game::camera.x;
            // rect_dest.y = static_cast<int>(transform->getPos().y) - Game::camera.y;

            rect_dest.x = transform->getPos().x;
            rect_dest.y = transform->getPos().y;
            rect_dest.w = transform->w() * transform->sc();
            rect_dest.h = transform->h() * transform->sc();

            if (vel != nullptr) {
                transform->getPosRef() += vel->getVelScaled();
                sprite_flip = vel->getVel().x > 0 ? SDL_FLIP_HORIZONTAL : vel->getVel().x < 0 ? SDL_FLIP_NONE : sprite_flip;

                if (accel != nullptr)
                    vel->getVelRef() += accel->getAccel();
            }
        }
    };

    void draw() {
        Game::assets.drawTex(tex, rect_src, rect_dest, sprite_flip);
    };

    void addAnim(std::string anim_name, std::string tex_key, int ss_row, int frames, int speed) {
        std::tuple<std::string, int, int, int> anim_data(tex_key, ss_row, frames, speed);
        animations.emplace(anim_name, anim_data);
    };

    void setCurAnim(std::string anim_name) {
        animated = true;
        setTex(std::get<0>(animations[anim_name]));
        ss_row = std::get<1>(animations[anim_name]);
        frames = std::get<2>(animations[anim_name]);
        speed = std::get<3>(animations[anim_name]);
    };
};