#pragma once

#include <SDL2/SDL.h>

#include "AssetManager.hpp"

class Game {
private:
    SDL_Window *window;

public:
    Game();
    ~Game();

    static SDL_Renderer* renderer;
    static SDL_Event event;

    void init(const char* title, int x, int y, int w, int h, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    static bool is_running;
    static SDL_Rect camera;
    static AssetManager* assets;

    enum group_labels : std::size_t {
        group_map,
        // group_players,
        // group_colliders,
        // group_projectiles
    };
};