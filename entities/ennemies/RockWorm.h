#ifndef ROCKWORM_H_INCLUDED
#define ROCKWORM_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class RockWorm : public Ennemy {
    public:
    RockWorm(IP& ip, Level& level);
    ~RockWorm();
    bool AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character);
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    float _outTime;
    sf::Clock _outTimer;
    sf::Clock _attackTimer;

    sf::IntRect _littleHitBox;
    sf::IntRect _bigHitBox;
    bool _shot;
};

#endif // ROCKWORM_H_INCLUDED
