#pragma once

#include <SDL2/SDL.h>

#include "AssetManager.hpp"

class Game {
private:
    SDL_Window* window;
    entt::registry registry;

public:
    Game(const char* title, int x, int y, int w, int h, bool fullscreen);
    ~Game();

    SDL_Renderer* renderer;
    SDL_Event event;
    bool is_running;
    SDL_Rect camera;
    AssetManager* assets;

    // enum group_labels : std::size_t {
    //     group_map,
    //     group_players,
    //     group_colliders,
    //     group_projectiles
    // };

    void handleEvents();
    void update();
    void render();
};