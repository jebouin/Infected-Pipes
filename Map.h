#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;

class Map {
    public:
    Map(IP& ip);
    ~Map();
    void Draw(IP& ip);
    bool IsOnMap(sf::Vector2i pos);
    int GetTile(sf::Vector2i pos);
    void SetTile(sf::Vector2i pos, int id);

    private:
    sf::Vector2i _size;
    sf::Sprite _tileset;
    vector<vector<int> > _tiles;
};

#endif // MAP_H_INCLUDED
