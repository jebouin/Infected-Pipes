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

class Ennemy : public GameEntity {
    public:
    Ennemy(IP& ip, string name, sf::IntRect hitbox, int hpn, int xp);
    ~Ennemy();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager);
    int GetXP();

    private:
    bool _inPipe;
    int _xp;
};

#endif // ENNEMY_H_INCLUDED
