#ifndef ARROW_H_INCLUDED
#define ARROW_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Bullet.h"

using namespace std;

class IP;
class Character;
class Level;
class ParticleManager;
class EntityManager;

class Arrow : public Bullet {
    public:
    Arrow(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy);
    ~Arrow();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);

    private:

};

#endif // ARROW_H_INCLUDED
