#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;
class Spawner;
class EntityManager;

class Level {
    public:
    Level(IP& ip);
    ~Level();
    void Update(IP& ip, EntityManager& eManager);
    void Draw(IP& ip);
    Map& GetMap();
    Spawner& GetSpawner();

    private:
    Map *_map;
    sf::Image _levelImage;
    Spawner *_spawner;
};

#endif // LEVEL_H_INCLUDED
