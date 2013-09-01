#ifndef MOVINGSPRITE_H_INCLUDED
#define MOVINGSPRITE_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;

class MovingSprite : public sf::Sprite {
    public:
    MovingSprite(IP& ip, string name);
    ~MovingSprite();
    void Update(IP& ip, float eTime);
    void Update(IP& ip, float eTime, Map& map);
    bool TryMove(sf::Vector2f delta, Map& map);
    sf::Vector2f GetVel();
    float GetRotVel();
    sf::Vector2f GetUpperLeftPos();
    void SetVel(sf::Vector2f vel);
    void Accelerate(sf::Vector2f vec, float eTime);
    void SetRotVel(float rotVel);

    private:
    sf::Vector2f _vel;
    float _rotVel;
};

#endif // MOVINGSPRITE_H_INCLUDED
