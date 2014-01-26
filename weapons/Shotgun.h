#ifndef SHOTGUN_H_INCLUDED
#define SHOTGUN_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Shotgun : public Weapon {
    public:
    Shotgun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~Shotgun();
    void Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager);

    private:

};

#endif // SHOTGUN_H_INCLUDED
