#include "../include/AssetManager.hpp"
#include "../include/Game.hpp"

AssetManager::AssetManager(entt::registry* registry, SDL_Renderer* renderer) {
    this->registry = registry;
    this->renderer = renderer;
};

AssetManager::~AssetManager() {
    // if (registry != nullptr)
    //     delete registry;
};

SDL_Texture* AssetManager::loadTex(const char* file_path) {
    SDL_Surface* temp_surface = IMG_Load(file_path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return(tex);
};

void AssetManager::drawTex(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, tex, &src, &dest, 0, NULL, flip);
};

void AssetManager::addTex(std::string id, const char* path) {
    tex_map.emplace(id, loadTex(path));
};

SDL_Texture* AssetManager::getTex(std::string id) {
    return tex_map[id];
};