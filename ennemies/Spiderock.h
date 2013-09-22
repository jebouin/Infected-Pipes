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
class BulletManager;

class Spiderock : public Ennemy {
    public:
    Spiderock(IP& ip);
    ~Spiderock();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);

    private:

};

#endif // ENNEMY_H_INCLUDED
