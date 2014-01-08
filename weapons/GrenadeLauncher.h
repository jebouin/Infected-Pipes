#ifndef GRENADELAUNCHER_H_INCLUDED
#define GRENADELAUNCHER_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"



class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class GrenadeLauncher : public Weapon {
    public:
    GrenadeLauncher(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~GrenadeLauncher();
    void Update(IP& ip, float eTime, BulletManager& bManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle);

    private:

};

#endif // GRENADELAUNCHER_H_INCLUDED
