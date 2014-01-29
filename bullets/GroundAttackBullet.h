#ifndef GROUNDATTACKBULLET_H_INCLUDED
#define GROUNDATTACKBULLET_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"

class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class GroundAttackBullet : public Bullet {
    public:
    GroundAttackBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy, float damage, float penetration, bool big);
    ~GroundAttackBullet();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

    private:

};

#endif // GROUNDATTACKBULLET_H_INCLUDED
