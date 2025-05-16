#include <fstream>

#include "../include/Map.hpp"
#include "../include/Game.hpp"
#include "../include/components/Tile.hpp"
#include "../include/components/Transform.hpp"
#include "../include/components/Collision.hpp"

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
    // map_path will have "_#" appended to it where # is a number for a layer
    // 0 = tiles, 1 = collision for layer 0, 2 = sprites, 3 = collision for layer 2
    // Layer 0 is mandatory

    char c;
    entt::entity cur_tile;
    std::fstream map_file, coll0_file;
    map_file.open(map_path + "_0");
    coll0_file.open(map_path + "_1");

    int x, y, src_x, src_y;

    for(y = 0; y < size_y; ++y) {
        for(x = 0; x < size_x; ++x) {
            map_file.get(c);
            src_y = atoi(&c) * tile_size;
            map_file.get(c);
            src_x = atoi(&c) * tile_size;
            cur_tile = addTile(src_x, src_y, x * scaled_size, y * scaled_size);
            map_file.ignore();

            if (coll0_file.is_open()) {
                coll0_file.get(c);
                
                if (c == '1') {
                    Transform& tile_trans = Game::registry.get<Transform>(cur_tile);
                    Game::registry.emplace<Collision>(cur_tile, tile_trans, true, 128);
                }

                coll0_file.ignore();
            }
        }
    }

    // map_file.ignore();

    // for(y = 0; y < size_y; ++y) {
    //     for(x = 0; x < size_x; ++x) {
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

entt::entity Map::addTile(int src_x, int src_y, float pos_x, float pos_y) {
    const auto tile = Game::registry.create();
    Transform& transform = Game::registry.emplace<Transform>(tile, pos_x, pos_y, tile_size, tile_size, map_scale);
    Game::registry.emplace<Tile>(tile, src_x, src_y, tex_id, transform);
    // tile.addGroup(Game::group_map);

    return(tile);
};