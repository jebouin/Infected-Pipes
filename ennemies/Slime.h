#ifndef SLIME_H_INCLUDED
#define SLIME_H_INCLUDED

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

class Slime : public Ennemy {
    public:
    Slime(IP& ip, Level& level);
    ~Slime();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
    sf::Clock _jumpTimer;
    float _nextJump;
};

#endif // SLIME_H_INCLUDED
