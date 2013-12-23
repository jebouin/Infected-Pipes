#ifndef FLYINGSKULL_H_INCLUDED
#define FLYINGSKULL_H_INCLUDED

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

class FlyingSkull : public Ennemy {
    public:
    FlyingSkull(IP& ip, Level& level);
    ~FlyingSkull();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
    sf::Clock _boneTimer;
    float _boneTime;
};

#endif // FLYINGSKULL_H_INCLUDED
