#pragma once

#include <entt.hpp>
#include <string>

class Map {
private:
    std::string tex_id;
    std::string map_path = "";

public:
    int map_scale;
    int tile_size;
    int scaled_size;
    int size_x; // # of tiles, horizontal
    int size_y; // # of tiles, vertical

    void setMap(std::string tex_id, std::string map_path, int map_scale, int tile_size, int size_x, int size_y);
    void loadMap();
    entt::entity addTile(int src_x, int src_y, float pos_x, float pos_y);
};