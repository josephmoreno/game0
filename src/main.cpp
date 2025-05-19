// Heavily referenced: https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&si=lpjEMfmYyjf_TN1X

#include "../include/Game.hpp"

int main(int argc, char** argv) {
    Game game;

    game.init("Game0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, false);

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

static void mainLoop(void) {
    const int fps = 60;
    const int frame_delay = 1000 / fps; // 1000 ms / fps = ms per frame

    Uint32 frame_start = SDL_GetTicks();;
    int frame_time;

    if (quit) {
        SdlObj0.close();
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #else
        exit(0);
        #endif
    }

	// Emulate a cycle of the Chip-8 architecture.
	Chip8.emulateCycle();

	// Render and update the screen if Chip8.dispFlag == 0x01.
	if (Chip8.dispFlag == 0x01)
		SdlObj0.drawScreen(Chip8);

    

	frame_time = SDL_GetTicks() - frame_start;

	if (frame_delay > frame_time)
		SDL_Delay(frame_delay - frame_time);
};

extern "C" {
	void normalQuit() {
		SdlObj0.close();
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #else
        exit(0);
        #endif
	}
};