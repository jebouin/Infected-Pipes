#ifndef SPAWNER_H_INCLUDED
#define SPAWNER_H_INCLUDED

#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class Pipe;
class IP;
class EntityManager;
class MovingSprite;
class Character;
class Level;
class GUI;

class Spawner {
    public:
    Spawner(IP& ip, int nbWaves, Level& l);
    ~Spawner();
    void Update(IP& ip, float eTime, EntityManager& eManager, Level& level, Character& character, GUI& gui);
    void Spawn(IP& ip, EntityManager& eManager, Level& level, Character& character);
    void Draw(IP& ip);
    bool SpawnCharacter(Character& character);
    void AddPipe(Pipe *p);
    bool IsFinished();
    bool CanEnterPipe(MovingSprite& s);
    bool IsCollided(sf::FloatRect rect);
    bool IsCollided(MovingSprite& sprite, sf::Vector2f pos);
    bool IsCollided(MovingSprite& sprite);
    bool IsOnGround(MovingSprite& sprite);

    private:
    void NextWave(IP& ip, Level& level, GUI& gui);

    std::vector<Pipe*> _pipes;
    int _curWave;
    int _nbWaves;
    float _difficulty;
    sf::Clock _clock;
    sf::Clock _nextWaveTimer;
    int _difToSpawn;
    bool _spawning;
    bool _finished;
};

#endif // SPAWNER_H_INCLUDED
