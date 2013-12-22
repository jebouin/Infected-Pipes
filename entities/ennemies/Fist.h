#ifndef FIST_H_INCLUDED
#define FIST_H_INCLUDED

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

class Fist : public Ennemy {
    public:
    enum State {SGOINGUP, SGOINGDOWN, SUP, SDOWN};

    Fist(IP& ip, Level& level);
    ~Fist();
    bool AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character);
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Vector2f _upPos;
    sf::Vector2f _downPos;
    sf::Clock _stateTimer;
    sf::Clock _attackTimer;
    sf::Clock _particleTimer;
    float _stateTime;
    State _curState;
};

#endif // FIST_H_INCLUDED
