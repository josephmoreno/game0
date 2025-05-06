#include <iostream>

#include "../include/Game.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::is_running = false;

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        Game::is_running = true;
    }else
        Game::is_running = false;

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
    return;
};

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return;
};

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;

    return;
};