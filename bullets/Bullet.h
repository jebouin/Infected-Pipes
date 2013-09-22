#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "MovingSprite.h"

using namespace std;

class IP;
class TextureLoader;
class Level;

class Bullet : public MovingSprite {
    public:
    Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, bool animated);
    ~Bullet();
    void Update(IP& ip, float eTime, Level& level);
    void Draw(IP& ip);

    private:

};

#endif // BULLET_H_INCLUDED
