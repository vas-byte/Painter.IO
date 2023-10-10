#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "tileFeature.h"
#include <vector>
#include "Object.h"

class TileMap : public sf::Drawable, public sf::Transformable{
    private:

        int tileMap[4500];

        //Load tiles from JSON file
        void load_tileMap();

        //Draw Map
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Store size of tiles
        sf::VertexArray m_vertices;
        
        //Store tilseset tetxure
        sf::Texture m_tileset;

        
        
    public:
        //Load Tileset
        bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

        //Get Map Features
       tileFeature* get_mapFeatures(int width, int row, int col, int id);
};

#endif