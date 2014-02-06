#ifndef ROCKWORM_H_INCLUDED
#define ROCKWORM_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class RockWorm : public Ennemy {
    public:
    enum State {SGOINGUP, SGOINGDOWN, SUP, SDOWN, SATTACKING};

    RockWorm(IP& ip, Level& level);
    ~RockWorm();
    bool AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character);
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    bool _attacked;
    sf::Clock _stateTimer;
    float _stateTime;
    State _curState;
    sf::Clock _attackTimer;
    sf::Vector2f _upPos;
    sf::Vector2f _downPos;
};

#endif // ROCKWORM_H_INCLUDED
