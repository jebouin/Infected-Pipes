#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

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
class GUI;
class Stalactite;
class SnowFlakes;
class Player;
class WaterGrass;
class Bubble;

struct LevelInfo {
    std::string _imageName;
    std::string _backgroundName;
    float _backgroundZoom;
    bool _addDucks;
    bool _addMice;
    bool _addSkulls;
};

class Level {
    public:
    Level(IP& ip, Player& player, ParticleManager& pManager);
    ~Level();
    void Update(IP& ip, EntityManager& eManager, Player& player, float eTime, ParticleManager& pManager, BulletManager& bManager, GUI& gui, sf::View& preView);
    void DrawBack(IP& ip, sf::View& prevView);
    void DrawFront(IP& ip, sf::View& prevView);
    Map& GetMap() const;
    Spawner& GetSpawner();
    void Load(IP& ip, std::string name, Player& player, ParticleManager& pManager);
    void NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Player& player, ParticleManager& pManager);
    int GetDifficulty() const;
    void SetDifficulty(int v);
    void OpenChest(Character& character, IP& ip);
    int GetNbWaterFields();
    WaterField& GetWaterField(int id);
    bool IsInWater(sf::Sprite spt, bool lava);
    void AddWaterFall(IP& ip, sf::Vector2i tilePos, bool big, bool lava);
    int GetNbPassiveEntities();
    GameEntity* GetPassiveEntity(int id);
    std::string GetName();
    void AddBubble(Bubble* b);

    private:
    sf::Clock _timer;
    sf::Clock _bubbleTimer;
    sf::Vector2i GetRectSizeInImageAt(sf::Image& img, sf::Vector2i pos, sf::Color c);

    Map *_map;
    std::vector<sf::Image> _levelImages;
    Spawner *_spawner;
    Grass *_grass;
    WaterGrass *_waterGrass;
    Background *_background;
    std::string _curLevel;
    std::map<std::string, LevelInfo> _levelInfos;

    int _difficulty;
    std::vector<Chest*> _chests;
    std::vector<WaterField*> _waterFields;
    std::vector<WaterFall*> _waterFalls;
    std::vector<GameEntity*> _passiveEntities;
    std::vector<sf::Sprite> _backSprites;
    std::vector<Stalactite*> _stalactites;
    std::vector<Bubble*> _bubbles;
    SnowFlakes *_flakes;

    sf::RenderTexture _lavaTexture;
    sf::Shader _lavaShader;
};

#endif // LEVEL_H_INCLUDED
