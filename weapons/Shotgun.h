#ifndef SHOTGUN_H_INCLUDED
#define SHOTGUN_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"

using namespace std;

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Shotgun : public Weapon {
    public:
    Shotgun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~Shotgun();
    void Update(IP& ip, float eTime, BulletManager& bManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle);

    private:

};

#endif // SHOTGUN_H_INCLUDED
