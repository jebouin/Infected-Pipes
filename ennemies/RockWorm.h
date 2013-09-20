#ifndef SPIDEROCK_H_INCLUDED
#define SPIDEROCK_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;

class RockWorm : public Ennemy {
    public:
    RockWorm(IP& ip);
    ~RockWorm();
    bool AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character);
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager);

    private:
    float _outTime;
    sf::Clock _outTimer;
    sf::Clock _attackTimer;
};

#endif // ENNEMY_H_INCLUDED
