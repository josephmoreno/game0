#pragma once

#include <string>

class Map {
private:
    std::string tex_id;
    int map_scale;
    int tile_size;
    int scaled_size;

public:
    void setMap(std::string tex_id, int map_scale, int tile_size);
    void loadMap(std::string path, int size_x, int size_y);
    void addTile(int src_x, int src_y, float pos_x, float pos_y);
};