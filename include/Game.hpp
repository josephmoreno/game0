#pragma once

#include <SDL2/SDL.h>
#include <entt.hpp>

#include "AssetManager.hpp"

class Game {
private:
    static SDL_Window* window;
    static entt::registry registry;

public:
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool is_running;
    static SDL_Rect camera;
    static AssetManager assets;

    // enum group_labels : std::size_t {
    //     group_map,
    //     group_players,
    //     group_colliders,
    //     group_projectiles
    // };

    void init(const char* title, int x, int y, int w, int h, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void cleanUp();
};