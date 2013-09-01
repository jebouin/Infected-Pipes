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
    Map(IP& ip, sf::Vector2i size);
    ~Map();
    void Draw(IP& ip);
    bool IsOnMap(sf::Vector2i pos);
    int GetTile(sf::Vector2i pos);
    sf::Vector2i GetSize();
    void SetTile(sf::Vector2i pos, int id);
    bool IsCollided(sf::FloatRect rect);
    bool IsCollided(MovingSprite& sprite, sf::Vector2f pos);
    bool IsCollided(MovingSprite& sprite);
    bool IsOnGround(MovingSprite& sprite);

    private:
    sf::Vector2i _size;
    sf::Sprite _tileset;
    vector<vector<int> > _tiles;
};

#endif // MAP_H_INCLUDED
