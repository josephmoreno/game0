// Heavily referenced: https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&si=lpjEMfmYyjf_TN1X

#include "../include/Game.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Game game;

static void mainLoop(void);

int main(int argc, char** argv) {
    game.init("Game0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, false);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);   
    #else
    while(1) { mainLoop(); }
    #endif

    return(0);
};

static void mainLoop(void) {
    if (!Game::is_running) {
        game.cleanUp();

        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #else
        exit(0);
        #endif
    }

    const int fps = 60;
    const int frame_delay = 1000 / fps; // 1000 ms / fps = ms per frame

    Uint32 frame_start = SDL_GetTicks();;
    int frame_time;

	game.handleEvents();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time)
        SDL_Delay(frame_delay - frame_time);
};

extern "C" {
	void normalQuit() {
		Game::is_running = false;
        
        // #ifdef __EMSCRIPTEN__
        // emscripten_cancel_main_loop();
        // #else
        // exit(0);
        // #endif
	}
};