#ifndef FIREWORMBOSS_H_INCLUDED
#define FIREWORMBOSS_H_INCLUDED

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

class FireWormBoss : public Ennemy {
public:
    FireWormBoss(IP& ip, Level& level);
    ~FireWormBoss();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

private:

};

#endif // FIREWORMBOSS_H_INCLUDED
