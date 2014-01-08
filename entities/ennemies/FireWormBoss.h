#ifndef FIREWORMBOSS_H_INCLUDED
#define FIREWORMBOSS_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class FireWormBoss : public Ennemy {
public:
    enum State {SDOWN, SUP, SGOINGDOWN, SGOINGUP, STURRETGOINGUP, STURRETGOINGDOWN, STURRETATTACKING};

    FireWormBoss(IP& ip, Level& level);
    ~FireWormBoss();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void ChangeState(State state);

private:
    float _upY;
    float _downY;
    float _relY;
    State _curState;
    sf::Clock _stateTimer;
    float _stateTime;

    //turret base
    sf::Sprite _turretBase;
    sf::Sprite _turretCannon;
    float _turUpY;
    float _turDownY;
    float _relTurretY;

    //cannon
    float _startCannonAngle;
    sf::Clock _cannonTimer;
};

#endif // FIREWORMBOSS_H_INCLUDED
