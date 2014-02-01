#ifndef BUBBLE_H_INCLUDED
#define BUBBLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

class IP;
class Map;

class Bubble : public sf::Sprite {
    public:
    Bubble(IP& ip, Map& map);
    ~Bubble();
    void Update(IP& ip, float eTime, Level& level);
    void Draw(IP& ip);
    bool IsAlive();

    private:
    bool _alive;
    float _timer;
    sf::Vector2f _relPos;
};

#endif // BUBBLE_H_INCLUDED
