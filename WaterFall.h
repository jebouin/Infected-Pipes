#ifndef WATERFALL_H_INCLUDED
#define WATERFALL_H_INCLUDED

#include <iostream>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "MovingSprite.h"

using namespace std;

class IP;
class ParticleManager;
class Level;

class WaterFall : public MovingSprite {
    public:
    WaterFall(IP& ip, sf::Vector2i tilePos);
    ~WaterFall();
    void Update(IP& ip, float elapsedTime, Level& level);
    void Draw(IP& ip);

    private:

};

#endif // WATERFALL_H_INCLUDED
