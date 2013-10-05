#ifndef LASERBULLET_H_INCLUDED
#define LASERBULLET_H_INCLUDED

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

class LaserBullet : public Bullet {
    public:
    LaserBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~LaserBullet();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

    private:

};

#endif // LASERBULLET_H_INCLUDED
