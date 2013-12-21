#ifndef STALACTITE_H_INCLUDED
#define STALACTITE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;
class Character;
class ParticleManager;
class EntityManager;

class Stalactite {
public:
    Stalactite(sf::Vector2i tilePos);
    ~Stalactite();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

private:
    sf::Sprite _base;
    sf::Sprite _stalactite;
    sf::Clock _regenTimer;
    sf::Clock _damageTimer;
    bool _separated;
    bool _dead;
    float _yVel;
};

#endif // STALACTITE_H_INCLUDED
