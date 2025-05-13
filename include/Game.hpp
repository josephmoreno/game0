#pragma once

#include <SDL2/SDL.h>
#include <entt.hpp>

#include "AssetManager.hpp"
#include "Map.hpp"

// Only static data members and methods because not currently designed for multiple Game instances

class Game {
private:
    static SDL_Window* window;
    static int cam_x_max, cam_y_max;

public:
    static int win_w, win_h;
    static entt::registry registry;
    static entt::entity player;
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool is_running;
    static SDL_Rect camera;
    static AssetManager assets;
    static Map cur_map;

    // enum group_labels : std::size_t {
    //     group_map,
    //     group_players,
    //     group_colliders,
    //     group_projectiles
    // };

    static void init(const char* title, int x, int y, int w, int h, bool fullscreen);
    static void handleEvents();
    static void update();
    static void render();
    static void cleanUp();
};