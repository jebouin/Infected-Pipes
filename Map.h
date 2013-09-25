#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class MovingSprite;

class Map {
    public:
    enum TileType {VOID, WALL, PLATFORM};
    enum Layer {BACK=0, FRONT=1};

    Map(IP& ip, sf::Vector2i size);
    ~Map();
    void DrawLayer(IP& ip, Layer layer);
    bool IsOnMap(sf::Vector2i pos);
    int GetTile(sf::Vector2i pos, Layer layer);
    int GetTileType(int tileId);
    int GetTileType(sf::Vector2i pos, Layer layer);
    sf::Vector2i GetSize();
    int GetNbNeighbours(sf::Vector2i pos, Layer layer);
    int GetNbDirNeigboursCode(sf::Vector2i pos, Layer layer);
    void SetTile(sf::Vector2i pos, int id, Layer layer);
    bool IsCollided(sf::FloatRect rect, TileType type);
    bool IsCollided(MovingSprite& sprite, sf::Vector2f pos, TileType type);
    bool IsCollided(MovingSprite& sprite, TileType type);
    bool IsOnTileType(MovingSprite& sprite, sf::Vector2f pos, TileType type);
    bool IsOnTileType(MovingSprite& sprite, TileType type);

    private:
    bool IsLocalCollided(sf::Vector2f pos, TileType type);

    sf::Vector2i _size;
    sf::Sprite _tileset;
    vector<vector<vector<int> > > _tiles;
    vector<TileType> _tileTypes;
};

#endif // MAP_H_INCLUDED
