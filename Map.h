#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class MovingSprite;

class Map {
    public:
    enum TileType {VOID, WALL, PLATFORM};
    enum Layer {BACK=0, FRONT=1};

    Map(IP& ip, sf::Vector2i size);
    ~Map();
    void DrawLayer(sf::RenderTexture& rt, Layer layer);
    bool IsOnMap(sf::Vector2i pos);
    int GetTile(sf::Vector2i pos, Layer layer);
    int GetTileType(int tileId);
    int GetTileType(sf::Vector2i pos, Layer layer);
    sf::Vector2i GetSize();
    int GetNbNeighbours(sf::Vector2i pos, Layer layer);
    int GetNbDirNeighboursCode(sf::Vector2i pos, Layer layer, bool diagonal);
    void SetTile(sf::Vector2i pos, int id, Layer layer);
    bool IsCollided(sf::FloatRect rect, TileType type);
    bool IsCollided(MovingSprite& sprite, sf::Vector2f pos, TileType type);
    bool IsCollided(MovingSprite& sprite, TileType type);
    bool IsOnTileType(sf::FloatRect rect, TileType type);
    bool IsOnTileType(MovingSprite& sprite, sf::Vector2f pos, TileType type);
    bool IsOnTileType(MovingSprite& sprite, TileType type);

    private:
    bool IsLocalCollided(sf::Vector2f pos, TileType type);

    sf::Vector2i _size;
    sf::Sprite _tileset;
    std::vector<std::vector<std::vector<int> > > _tiles;
    std::vector<TileType> _tileTypes;
};

#endif // MAP_H_INCLUDED
