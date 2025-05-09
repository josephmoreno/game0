#include <iostream>

#include "../include/components/Components.hpp"
#include "../include/Game.hpp"

SDL_Window* Game::window = nullptr;
entt::registry Game::registry;
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
bool Game::is_running;
SDL_Rect Game::camera;
AssetManager Game::assets;

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

    // Create entities
    const auto player = Game::registry.create();

    // Assign components to entities
    Game::registry.emplace<Transform>(player, 320, 320, 32, 32, 1);
    Game::registry.emplace<Velocity>(player);
    Game::registry.emplace<Acceleration>(player);
    Game::registry.emplace<Sprite>(player, "NumboIdle", "ss_numbo", 0, 12, 100, Game::registry.get<Transform>(player), Game::registry.get<Velocity>(player), Game::registry.get<Acceleration>(player));
    Game::registry.get<Sprite>(player).addAnim("NumboWalk", "ss_numbo", 1, 6, 100);
    Game::registry.emplace<KeyboardControl>(player, Game::registry.get<Sprite>(player));

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

        // Sprite& sprite = group.get<Sprite>(entity);
        // KeyboardControl& kc = group.get<KeyboardControl>(entity);

        // sprite.update();
        // kc.update();
    }

    return;
};

void Game::render() {
    SDL_RenderClear(Game::renderer);

    auto view = Game::registry.view<Sprite>();
    for(auto entity : view)
        view.get<Sprite>(entity).draw();

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