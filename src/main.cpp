// Heavily referenced: https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&si=lpjEMfmYyjf_TN1X

#include "../include/Game.hpp"

int main(int argc, char** argv) {
    const int fps = 60;
    const int frame_delay = 1000 / fps; // 1000 ms / fps = ms per frame

    Uint32 frame_start;
    int frame_time;

    Game game;

    game.init("Game0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, true);

    while(Game::is_running) {
        frame_start = SDL_GetTicks();

        game.handleEvents();
        game.update();
        game.render();

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }

    game.cleanUp();

    return(0);
};