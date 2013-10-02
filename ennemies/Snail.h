#ifndef SNAIL_H_INCLUDED
#define SNAIL_H_INCLUDED

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

class Snail : public Ennemy {
    public:
    Snail(IP& ip);
    ~Snail();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);

    private:
    sf::Clock _attackTimer;
};

#endif // SNAIL_H_INCLUDED
