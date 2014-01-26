#ifndef RIFLE_H_INCLUDED
#define RIFLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Rifle : public Weapon {
    public:
    Rifle(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~Rifle();
    void Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager);

    private:

};

#endif // RIFLE_H_INCLUDED
