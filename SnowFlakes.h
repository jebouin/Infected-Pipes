#ifndef SNOWFLAKES_H_INCLUDED
#define SNOWFLAKES_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class Level;
class ParticleManager;

class SnowFlakes {
public:
    SnowFlakes(IP& ip);
    ~SnowFlakes();
    void Reset();
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager, sf::View& prevView);
    void Draw(IP& ip, sf::View& prevView);

private:
    sf::VertexArray _points;
    std::vector<sf::Vector2f> _vels;
    std::vector<sf::Vector2f> _basePos;
    sf::Vector2u _ssize;
    sf::View _view;
};

#endif // SNOWFLAKES_H_INCLUDED
