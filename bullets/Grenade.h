#ifndef GRENADE_H_INCLUDED
#define GRENADE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"

using namespace std;

class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class Grenade : public Bullet {
    public:
    Grenade(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~Grenade();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

    private:
    sf::Clock _explosionTimer;
};

#endif // GRENADE_H_INCLUDED
