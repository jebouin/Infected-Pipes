#ifndef TURTLE_H_INCLUDED
#define TURTLE_H_INCLUDED

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

class Turtle : public Ennemy {
    public:
    Turtle(IP& ip, Level& level);
    ~Turtle();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
    sf::Clock _fireballTimer;
    sf::Clock _fireTimer;
    bool _inLava;
    float _mPos;
};

#endif // TURTLE_H_INCLUDED
