#pragma once

#include "../Game.hpp"
#include "Sprite.hpp"

class KeyboardControl final {
public:
    Sprite* sprite;

    KeyboardControl(Sprite& sprite) {
        this->sprite = &sprite;
    };

    ~KeyboardControl() {};

    void update() {
        if (Game::event.type == SDL_KEYDOWN) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    sprite->vel->getVelRef().y = -1;
                    sprite->setCurAnim("NumboWalk");
                    break;

                case SDLK_a:
                    sprite->vel->getVelRef().x = -1;
                    sprite->setCurAnim("NumboWalk");
                    break;

                case SDLK_s:
                    sprite->vel->getVelRef().y = 1;
                    sprite->setCurAnim("NumboWalk");
                    break;

                case SDLK_d:
                    sprite->vel->getVelRef().x = 1;
                    sprite->setCurAnim("NumboWalk");
                    break;

                case SDLK_ESCAPE:
                    Game::is_running = false;
                    break;

                default:
                    break;
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    sprite->vel->getVelRef().y = 0;
                    sprite->setCurAnim("NumboIdle");
                    break;

                case SDLK_a:
                    sprite->vel->getVelRef().x = 0;
                    sprite->setCurAnim("NumboIdle");
                    break;

                case SDLK_s:
                    sprite->vel->getVelRef().y = 0;
                    sprite->setCurAnim("NumboIdle");
                    break;

                case SDLK_d:
                    sprite->vel->getVelRef().x = 0;
                    sprite->setCurAnim("NumboIdle");
                    break;

                default:
                    break;
            }
        }
    };
};