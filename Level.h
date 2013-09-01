#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;

class Level {
    public:
    Level(IP& ip);
    ~Level();
    void Draw(IP& ip);
    Map& GetMap();

    private:
    Map *_map;
    sf::Image _levelImage;
    sf::Sprite _pipe;
};

#endif // LEVEL_H_INCLUDED
