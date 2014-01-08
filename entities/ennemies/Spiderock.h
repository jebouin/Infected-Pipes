#ifndef SPIDEROCK_H_INCLUDED
#define SPIDEROCK_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Spiderock : public Ennemy {
    public:
    Spiderock(IP& ip, Level& level);
    ~Spiderock();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
};

#endif // SPIDEROCK_H_INCLUDED
