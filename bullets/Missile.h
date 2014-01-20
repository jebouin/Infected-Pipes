#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"

class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class Missile : public Bullet {
    public:
    Missile(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~Missile();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);
    bool Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _smokeTimer;
    sf::Vector2f _prevPos;
};

#endif // MISSILE_H_INCLUDED
