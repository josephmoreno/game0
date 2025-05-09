#include "../include/AssetManager.hpp"
#include "../include/Game.hpp"

AssetManager::~AssetManager() {
    for(auto map_item : tex_map)
        SDL_DestroyTexture(map_item.second);
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

void AssetManager::addTex(std::string id, const char* path) {
    tex_map.emplace(id, loadTex(path));
};

SDL_Texture* AssetManager::getTex(std::string id) {
    return tex_map[id];
};