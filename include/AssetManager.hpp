#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class AssetManager {
private:
    std::map<std::string, SDL_Texture*> tex_map;

public:
    ~AssetManager();

    static SDL_Texture* loadTex(const char* file_path);
    static void drawTex(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
    void addTex(std::string id, const char* path);
    SDL_Texture* getTex(std::string id);
};