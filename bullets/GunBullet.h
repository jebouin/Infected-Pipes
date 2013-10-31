#ifndef GUNBULLET_H_INCLUDED
#define GUNBULLET_H_INCLUDED

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

class GunBullet : public Bullet {
    public:
    GunBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~GunBullet();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

    private:

};

#endif // GUNBULLET_H_INCLUDED