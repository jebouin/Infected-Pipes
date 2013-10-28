#ifndef FIREBALL_H_INCLUDED
#define FIREBALL_H_INCLUDED

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

class FireBall : public Ennemy {
    public:
    FireBall(IP& ip, Level& level);
    ~FireBall();
    bool AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character);
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void SpreadParticles(IP& ip, ParticleManager& pManager);

    private:
    sf::Clock _attackTimer;
    sf::Clock _jumpTimer;
    bool _jumping;
};

#endif // FIREBALL_H_INCLUDED
