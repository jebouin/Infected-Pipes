#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;
class Spawner;
class EntityManager;
class Background;
class Grass;

struct LevelInfo {
    string _imageName;
    string _backgroundName;
};

class Level {
    public:
    Level(IP& ip);
    ~Level();
    void Update(IP& ip, EntityManager& eManager);
    void DrawBack(IP& ip, sf::View& prevView);
    void DrawFront(IP& ip);
    Map& GetMap();
    Spawner& GetSpawner();
    void Load(IP& ip, string name);

    private:
    Map *_map;
    sf::Image _levelImage;
    Spawner *_spawner;
    Grass *_grass;
    Background *_background;
    map<string, LevelInfo> _levelInfos;
};

#endif // LEVEL_H_INCLUDED
