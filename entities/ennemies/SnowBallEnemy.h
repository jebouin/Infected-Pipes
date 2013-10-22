#ifndef SNOWBALLENEMY_H_INCLUDED
#define SNOWBALLENEMY_H_INCLUDED

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

class SnowBallEnemy : public Ennemy {
    public:
    SnowBallEnemy(IP& ip, Level& level);
    ~SnowBallEnemy();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:

};

#endif // SNOWBALLENEMY_H_INCLUDED
