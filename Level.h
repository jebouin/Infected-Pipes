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
class BulletManager;
class Background;
class Grass;
class Character;

struct LevelInfo {
    string _imageName;
    string _backgroundName;
    float _backgroundZoom;
};

class Level {
    public:
    Level(IP& ip, Character& character);
    ~Level();
    void Update(IP& ip, EntityManager& eManager, Character& character);
    void DrawBack(IP& ip, sf::View& prevView);
    void DrawFront(IP& ip);
    Map& GetMap();
    Spawner& GetSpawner();
    void Load(IP& ip, string name, Character& character);
    void NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Character& character);

    private:
    Map *_map;
    sf::Image _levelImage;
    Spawner *_spawner;
    Grass *_grass;
    Background *_background;
    string _curLevel;
    map<string, LevelInfo> _levelInfos;
};

#endif // LEVEL_H_INCLUDED
