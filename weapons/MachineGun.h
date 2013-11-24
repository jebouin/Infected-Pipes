#ifndef MACHINEGUN_H_INCLUDED
#define MACHINEGUN_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"

using namespace std;

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class MachineGun : public Weapon {
    public:
    MachineGun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~MachineGun();
    void Update(IP& ip, float eTime, BulletManager& bManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle);

    private:

};

#endif // MACHINEGUN_H_INCLUDED
