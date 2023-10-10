#include "../Headers/tileMap.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "../Headers/Object.h"

void TileMap::load_tileMap(){
    //init JSON object
    nlohmann::json j;
    std::ifstream ifs("State/map.json");

    //open JSON file
    if (!ifs.is_open())
        {
            //return false;;
        }

    //Write file to JSON object
    ifs >> j;

    //Close file IO
    ifs.close();

    //index in array for map (tile indicies)
    int i = 0;

    //Loads map from JSON file with list of tile indices
    for (int elem : j["map"]){
        tileMap[i] = elem;
        i++;
    }
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    //Load tileset arrangement into array
    load_tileMap();

    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tileMap[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

//Gets an array of map features
tileFeature* TileMap::get_mapFeatures(int width, int row, int col, int id){
    
    if(tileMap[col + row * width] != 12)
        return nullptr;

    //Loads map features into vector
    tileFeature* feature = new tileFeature(id, col * 16, row * 16);
    
    return feature;
}
