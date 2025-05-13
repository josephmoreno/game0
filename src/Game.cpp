#include <iostream>

#include "../include/Game.hpp"
#include "../include/components/Components.hpp"

int Game::win_w = -1;
int Game::win_h = -1;
SDL_Window* Game::window = nullptr;
int Game::cam_x_max = 0;
int Game::cam_y_max = 0;

entt::registry Game::registry;
entt::entity Game::player;
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

        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window) {
            std::cout << "Window created" << std::endl;
            win_w = w;
            win_h = h;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 100, 147, 237, 255);
            std::cout << "Renderer created" << std::endl;
        }

        is_running = true;

        // Add assets to asset manager
        assets.addTex("ss_numbo", "assets/ss_numbo.png");
        assets.addTex("ts_map0", "assets/ts_map0.png");

        // Set map and the camera
        cur_map.setMap("ts_map0", "assets/map0.csv", 2, 32, 25, 20);
        camera = {0, 0, w, h};
        cam_x_max = (cur_map.size_x * cur_map.scaled_size) - win_w;
        cam_y_max = (cur_map.size_y * cur_map.scaled_size) - win_h;

        // Create entities
        cur_map.loadMap();  // loadMap() creates entities with tile components
        player = registry.create();

        // Assign components to entities
        Transform& player_trans = registry.emplace<Transform>(player, 320, 320, 32, 32, 2);
        Velocity& player_vel = registry.emplace<Velocity>(player, 2);
        Acceleration& player_accel = registry.emplace<Acceleration>(player);
        Sprite& player_sprite = registry.emplace<Sprite>(player, "Idle", "ss_numbo", 0, 12, 100, player_trans, player_vel, player_accel);
        player_sprite.addAnim("Walk", "ss_numbo", 1, 6, 100);
        registry.emplace<KeyboardControl>(player, player_sprite);
    }else
        is_running = false;

    return;
};

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            is_running = false;
            break;

        default:
            break;
    }

    return;
};

void Game::update() {
    // *** Code for grouping entities with certain components
    // auto group = registry.group<Sprite>(entt::get<KeyboardControl>);
    // for(auto entity : group) {
    //     auto[sprite, kc] = group.get<Sprite, KeyboardControl>(entity);
    //     sprite.update();
    //     kc.update();
    // }

    auto map_view = registry.view<Tile>();
    for(auto entity : map_view)
        map_view.get<Tile>(entity).update();

    // Update the camera position
    Transform player_trans = registry.get<Transform>(player);
    camera.x = player_trans.getPos().x - ((win_w / 2) - ((player_trans.w() * player_trans.sc()) / 2));
    camera.y = registry.get<Transform>(player).getPos().y - ((win_h / 2) - ((player_trans.h() * player_trans.sc()) / 2));

    if (camera.x < 0)
        camera.x = 0;
    
    if (camera.y < 0)
        camera.y = 0;

    if (camera.x > cam_x_max)
        camera.x = cam_x_max;

    if (camera.y > cam_y_max)
        camera.y = cam_y_max;

    auto[player_sprite, player_kc] = registry.get<Sprite, KeyboardControl>(player);
    player_sprite.update(player_trans.getPos().x - camera.x, player_trans.getPos().y - camera.y);
    player_kc.update();

    return;
};

void Game::render() {
    SDL_RenderClear(renderer);

    auto map_view = registry.view<Tile>();
    for(auto entity : map_view)
        map_view.get<Tile>(entity).draw();

    // auto sprite_view = registry.view<Sprite>();
    // for(auto entity : sprite_view)
    //     sprite_view.get<Sprite>(entity).draw();

    registry.get<Sprite>(player).draw();

    SDL_RenderPresent(renderer);

    return;
};

void Game::cleanUp() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;

    return;
};