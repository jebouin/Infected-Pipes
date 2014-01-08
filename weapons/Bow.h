#ifndef BOW_H_INCLUDED
#define BOW_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"



class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Bow : public Weapon {
    public:
    Bow(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~Bow();
    void Update(IP& ip, float eTime, BulletManager& bManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle);

    private:

};

#endif // BOW_H_INCLUDED
