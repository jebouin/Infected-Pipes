#ifndef SNAIL_H_INCLUDED
#define SNAIL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Snail : public Ennemy {
    public:
    Snail(IP& ip, Level& level);
    ~Snail();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);

    private:
    void UpdateCircle(sf::Vector2f eyePos);

    bool _preparing;
    float _nextAttack;
    sf::Clock _attackTimer;
    sf::Clock _particleTimer;
    sf::Clock _explodeTimer;

    sf::CircleShape _circle;
};

#endif // SNAIL_H_INCLUDED
