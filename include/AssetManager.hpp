#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class AssetManager {
private:
    static std::map<std::string, SDL_Texture*> tex_map;
    static std::map<std::string, Mix_Music*> music_map;
    static std::string cur_music;
    static std::map<std::string, Mix_Chunk*> sfx_map;

public:
    ~AssetManager();

    static SDL_Texture* loadTex(const char* file_path);
    static void drawTex(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
    static void drawAlphaRect(SDL_Rect dest, Uint8 alpha);
    static void addTex(std::string id, const char* path);
    static SDL_Texture* getTex(std::string id);
    static Mix_Music* loadMusic(const char* path);
    static void addMusic(std::string id, const char* path);
    static void setMusic(std::string id);
    static void toggleMusic();
    static Mix_Chunk* loadSfx(const char* path);
    static void addSfx(std::string id, const char* path);
    static void playSfx(std::string id, Uint8 volume, int loops);
};