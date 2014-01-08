#ifndef WATERFALL_H_INCLUDED
#define WATERFALL_H_INCLUDED

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "MovingSprite.h"



class IP;
class ParticleManager;
class Level;

class WaterFall : public MovingSprite {
    public:
    WaterFall(IP& ip, sf::Vector2i tilePos, bool big, bool lava);
    ~WaterFall();
    void Update(IP& ip, float elapsedTime, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    void Fall(IP& ip, Level& level);
    bool IsLava();

    private:
    sf::Clock _splashTimer;
    sf::Vector2i _tilePos;
    bool _big;
    bool _down;
    bool _lava;
    sf::ConvexShape _shape;
};

#endif // WATERFALL_H_INCLUDED
