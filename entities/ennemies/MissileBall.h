#ifndef MISSILEBALL_H_INCLUDED
#define MISSILEBALL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class MissileBall : public Ennemy {
    public:
    MissileBall(IP& ip, Level& level);
    ~MissileBall();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    int _state;
    sf::Clock _attackTimer;
    sf::Clock _missileTimer;
    sf::Clock _prepareTimer;
    float _attackTime;
    float _missileTime;
};

#endif // MISSILEBALL_H_INCLUDED
