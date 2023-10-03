#include "../Headers/Game.h"

Game::Game(){
    width = 1440;
    height = 800;
    map = TileMap();

    // define the level with an array of tile indices
    int level[4500];
    std::fill_n(level, 4500, 6);
    map.load("Assets/Tileset.png", sf::Vector2u(16, 16), level, 90, 50);
}

int Game::get_width(){
    return width;
}

int Game::get_height(){
    return height;
}

TileMap Game::get_map(){
    return map;
}