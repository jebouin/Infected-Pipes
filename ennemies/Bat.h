#ifndef BAT_H_INCLUDED
#define BAT_H_INCLUDED

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

class Bat : public Ennemy {
    public:
    Bat(IP& ip, Level& level);
    ~Bat();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager);

    private:

};

#endif // ENNEMY_H_INCLUDED
