#ifndef SNOWMAN_H_INCLUDED
#define SNOWMAN_H_INCLUDED

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

class SnowMan : public Ennemy {
    public:
    SnowMan(IP& ip, Level& level);
    ~SnowMan();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
};

#endif // SNOWMAN_H_INCLUDED
