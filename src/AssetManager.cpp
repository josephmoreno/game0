#include "../include/AssetManager.hpp"
#include "../include/Game.hpp"

std::map<std::string, SDL_Texture*> AssetManager::tex_map;
std::map<std::string, Mix_Music*> AssetManager::music_map;
std::string AssetManager::cur_music = "";
std::map<std::string, Mix_Chunk*> AssetManager::sfx_map;

AssetManager::~AssetManager() {
    for(auto map_item : tex_map)
        SDL_DestroyTexture(map_item.second);

    for(auto map_item : music_map)
        Mix_FreeMusic(map_item.second);

    for(auto map_item : sfx_map)
        Mix_FreeChunk(map_item.second);
};

SDL_Texture* AssetManager::loadTex(const char* file_path) {
    SDL_Surface* temp_surface = IMG_Load(file_path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return(tex);
};

void AssetManager::drawTex(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, NULL, flip);
};

void AssetManager::drawAlphaRect(SDL_Rect dest, Uint8 alpha) {
    SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, alpha);
    SDL_RenderFillRect(Game::renderer, &dest);
    SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
};

void AssetManager::addTex(std::string id, const char* path) {
    tex_map.emplace(id, loadTex(path));
};

SDL_Texture* AssetManager::getTex(std::string id) {
    return tex_map[id];
};

Mix_Music* AssetManager::loadMusic(const char* path) {
    Mix_Music* music = Mix_LoadMUS(path);

    return(music);
};

void AssetManager::addMusic(std::string id, const char* path) {
    music_map.emplace(id, loadMusic(path));
};

void AssetManager::setMusic(std::string id) {
    cur_music = id;
};

void AssetManager::toggleMusic() {
    // If no music is active...
    if (Mix_PlayingMusic() == 0) {

        // ...then play the music.
        Mix_PlayMusic(music_map[cur_music], -1);

    // If music is already active...
    } else{

        Mix_HaltMusic();

        // // ...if it's paused...
        // if (Mix_PausedMusic() == 1) {

        //     // ...then resume it.
        //     Mix_ResumeMusic();

        // // ...if it's playing...
        // }else {

        //     // ...then pause it.
        //     Mix_PauseMusic();
        // }
    }
};

Mix_Chunk* AssetManager::loadSfx(const char* path) {
    Mix_Chunk* sfx = Mix_LoadWAV(path);

    return(sfx);
};

void AssetManager::addSfx(std::string id, const char* path) {
    sfx_map.emplace(id, loadSfx(path));
};

void AssetManager::playSfx(std::string id, Uint8 volume, int loops) {
    Mix_VolumeChunk(sfx_map[id], volume);
    Mix_PlayChannel(-1, sfx_map[id], loops);
};