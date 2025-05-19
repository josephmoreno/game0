#pragma once

#include <SDL2/SDL.h>
#include <entt.hpp>

#include "../Game.hpp"
#include "Transform.hpp"
#include "Button.hpp"

class MouseControl final {
private:
    entt::entity ent;
    SDL_Rect rect_dest; // Assuming ent's position never changes, this rect's bounds don't change after construction
    Button* btn;

    bool withinRectDest(SDL_MouseButtonEvent e) {
        return (
            e.x >= rect_dest.x &&
            e.x < rect_dest.x + rect_dest.w &&
            e.y >= rect_dest.y &&
            e.y < rect_dest.y + rect_dest.h
        );
    };

public:
    MouseControl(entt::entity ent) {    // ent should have some transform that tells us its position on screen.
        this->ent = ent;
        Transform trans = Game::registry.get<Transform>(ent);
        btn = &Game::registry.get<Button>(ent);

        rect_dest.x = trans.getPos().x;
        rect_dest.y = trans.getPos().y;
        rect_dest.w = trans.w() * trans.sc();
        rect_dest.h = trans.h() * trans.sc();
    };

    ~MouseControl() {};

    void update() {
        if ((Game::event.type == SDL_MOUSEBUTTONUP) && withinRectDest(Game::event.button)) {
            switch(Game::event.button.button) {
                case 1: // Left-click
                    btn->toggleBtn();
                    break;

                default:
                    break;
            }
        }
    };
};