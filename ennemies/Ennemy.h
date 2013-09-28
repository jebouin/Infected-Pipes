#ifndef ENNEMY_H_INCLUDED
#define ENNEMY_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Ennemy : public GameEntity {
    public:
    enum EnnemyType {SPIDEROCK, ROCKWORM, BAT};

    Ennemy(IP& ip, string name, sf::IntRect hitbox, int hpn, int xp, int incDifficulty);
    ~Ennemy();
    virtual void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    int GetXP();
    int GetIncDifficulty();

    private:
    bool _inPipe;
    int _xp;
    int _incDifficulty;
};

#endif // ENNEMY_H_INCLUDED
