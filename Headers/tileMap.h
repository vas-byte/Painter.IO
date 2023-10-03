#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable{
    private:
        //Draw Map
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Store size of tiles
        sf::VertexArray m_vertices;
        
        //Store tilseset tetxure
        sf::Texture m_tileset;
        
    public:
        //Load Tileset
        bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

};

#endif