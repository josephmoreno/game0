#include <iostream>

#include "../include/Game.hpp"

Game::Game(const char* title, int x, int y, int w, int h, bool fullscreen) {
    int flags = 0;
    
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL sub-systems initialized" << std::endl;

        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window)
            std::cout << "Window created" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 100, 147, 237, 255);
            std::cout << "Renderer created" << std::endl;
        }

        is_running = true;

        assets = new AssetManager(&registry, renderer);
    }else
        is_running = false;

    return;
};

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;

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
    return;
};

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return;
};