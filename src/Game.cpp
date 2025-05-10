#include <iostream>

#include "../include/Game.hpp"
#include "../include/components/Components.hpp"

SDL_Window* Game::window = nullptr;
entt::registry Game::registry;
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
bool Game::is_running;
SDL_Rect Game::camera;
AssetManager Game::assets;
Map Game::cur_map;

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
    int flags = 0;
    
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL sub-systems initialized" << std::endl;

        Game::window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (Game::window)
            std::cout << "Window created" << std::endl;

        renderer = SDL_CreateRenderer(Game::window, -1, 0);
        if (Game::renderer) {
            SDL_SetRenderDrawColor(Game::renderer, 100, 147, 237, 255);
            std::cout << "Renderer created" << std::endl;
        }

        Game::is_running = true;
    }else
        Game::is_running = false;

    // Add assets to asset manager
    Game::assets.addTex("ss_numbo", "assets/ss_numbo.png");
    Game::assets.addTex("ts_map0", "assets/ts_map0.png");

    // Create entities
    Game::cur_map.setMap("ts_map0", 2, 32);
    Game::cur_map.loadMap("assets/map0.csv", 25, 20);   // loadMap() creates entities with tile components
    const auto player = Game::registry.create();

    // Assign components to entities
    Transform& player_trans = Game::registry.emplace<Transform>(player, 320, 320, 32, 32, 2);
    Velocity& player_vel = Game::registry.emplace<Velocity>(player, 2);
    Acceleration& player_accel = Game::registry.emplace<Acceleration>(player);
    Sprite& player_sprite = Game::registry.emplace<Sprite>(player, "Idle", "ss_numbo", 0, 12, 100, player_trans, player_vel, player_accel);
    player_sprite.addAnim("Walk", "ss_numbo", 1, 6, 100);
    Game::registry.emplace<KeyboardControl>(player, player_sprite);

    return;
};

void Game::handleEvents() {
    SDL_PollEvent(&Game::event);

    switch(Game::event.type) {
        case SDL_QUIT:
            Game::is_running = false;
            break;

        default:
            break;
    }

    return;
};

void Game::update() {
    auto group = Game::registry.group<Sprite>(entt::get<KeyboardControl>);
    for(auto entity : group) {
        auto[sprite, kc] = group.get<Sprite, KeyboardControl>(entity);
        sprite.update();
        kc.update();
    }

    return;
};

void Game::render() {
    SDL_RenderClear(Game::renderer);

    auto map_view = Game::registry.view<Tile>();
    for(auto entity : map_view)
        map_view.get<Tile>(entity).draw();

    auto sprite_view = Game::registry.view<Sprite>();
    for(auto entity : sprite_view)
        sprite_view.get<Sprite>(entity).draw();

    SDL_RenderPresent(Game::renderer);

    return;
};

void Game::cleanUp() {
    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;

    return;
};