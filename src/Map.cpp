#include <fstream>

#include "../include/Map.hpp"
#include "../include/Game.hpp"
#include "../include/components/Tile.hpp"
#include "../include/components/Transform.hpp"

void Map::setMap(std::string tex_id, std::string map_path, int map_scale, int tile_size, int size_x, int size_y) {
    this->tex_id = tex_id;
    this->map_path = map_path;
    this->map_scale = map_scale;
    this->tile_size = tile_size;
    scaled_size = map_scale * tile_size;
    this->size_x = size_x;
    this->size_y = size_y;
};

void Map::loadMap() {
    char c;
    std::fstream map_file;
    map_file.open(map_path);

    int src_x, src_y;

    for(int y = 0; y < size_y; ++y) {
        for(int x = 0; x < size_x; ++x) {
            map_file.get(c);
            src_y = atoi(&c) * tile_size;
            map_file.get(c);
            src_x = atoi(&c) * tile_size;
            addTile(src_x, src_y, x * scaled_size, y * scaled_size);
            map_file.ignore();
        }
    }

    // map_file.ignore();

    // for(int y = 0; y < size_y; ++y) {
    //     for(int x = 0; x < size_x; ++x) {
    //         map_file.get(c);
            
    //         if (c == '1') {
    //             auto& t_col(manager.addEntity());
    //             t_col.addComponent<ColliderComponent>("terrain", x * scaled_size, y * scaled_size, scaled_size);
    //             t_col.addGroup(Game::group_colliders);
    //         }

    //         map_file.ignore();
    //     }
    // }
};

void Map::addTile(int src_x, int src_y, float pos_x, float pos_y) {
    const auto tile = Game::registry.create();
    Transform& transform = Game::registry.emplace<Transform>(tile, pos_x, pos_y, tile_size, tile_size, map_scale);
    Game::registry.emplace<Tile>(tile, src_x, src_y, tex_id, transform);
    // tile.addGroup(Game::group_map);
};