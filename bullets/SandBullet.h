#ifndef SANDBULLET_H_INCLUDED
#define SANDBULLET_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"

class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class SandBullet : public Bullet {
    public:
    SandBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~SandBullet();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);
    bool Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:

};

#endif // SANDBULLET_H_INCLUDED
