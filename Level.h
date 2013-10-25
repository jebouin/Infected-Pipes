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
class Chest;
class WaterField;
class ParticleManager;
class WaterFall;
class Duck;
class GameEntity;

struct LevelInfo {
    string _imageName;
    string _backgroundName;
    float _backgroundZoom;
    bool _addDucks;
    bool _addMice;
};

class Level {
    public:
    Level(IP& ip, Character& character);
    ~Level();
    void Update(IP& ip, EntityManager& eManager, Character& character, float eTime, ParticleManager& pManager, BulletManager& bManager);
    void DrawBack(IP& ip, sf::View& prevView);
    void DrawFront(IP& ip);
    Map& GetMap() const;
    Spawner& GetSpawner();
    void Load(IP& ip, string name, Character& character);
    void NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Character& character);
    int GetDifficulty() const;
    void SetDifficulty(int v);
    void OpenChest(Character& character, IP& ip);
    int GetNbWaterFields();
    WaterField& GetWaterField(int id);
    void AddWaterFall(IP& ip, sf::Vector2i tilePos, bool big);
    int GetNbPassiveEntities();
    GameEntity* GetPassiveEntity(int id);
    string GetName();

    private:
    sf::Vector2i GetRectSizeInImageAt(sf::Image& img, sf::Vector2i pos, sf::Color& c);

    Map *_map;
    vector<sf::Image> _levelImages;
    Spawner *_spawner;
    Grass *_grass;
    Background *_background;
    string _curLevel;
    map<string, LevelInfo> _levelInfos;

    int _difficulty;
    vector<Chest*> _chests;
    vector<WaterField*> _waterFields;
    vector<WaterFall*> _waterFalls;
    vector<GameEntity*> _passiveEntities;
};

#endif // LEVEL_H_INCLUDED
