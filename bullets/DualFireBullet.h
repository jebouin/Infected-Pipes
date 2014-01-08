#ifndef DUALFIREBULLET_H_INCLUDED
#define DUALFIREBULLET_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"



class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class DualFireBullet : public Bullet {
public:
    DualFireBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~DualFireBullet();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

private:

};

#endif // DUALFIREBULLET_H_INCLUDED
