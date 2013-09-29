#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "MovingSprite.h"

using namespace std;

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Weapon : public MovingSprite {
    public:
    Weapon(IP& ip, string name, sf::IntRect hitbox, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime);
    virtual ~Weapon();
    virtual void Update(IP& ip, float eTime, BulletManager& bManager);
    virtual void Draw(IP& ip);
    virtual bool Use(IP& ip, BulletManager& bManager);

    private:
    const GameEntity& _holder;
    sf::Clock _useTimer;
    float _reloadTime;
    sf::Vector2f _relativePos;
};

#endif // WEAPON_H_INCLUDED
