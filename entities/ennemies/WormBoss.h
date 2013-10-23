#ifndef WORMBOSS_H_INCLUDED
#define WORMBOSS_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Boss.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class WormBoss : public Boss {
public:
    enum State {IDLE, PREPARING, JUMPING, GOINGUP, GOINGDOWN, INGROUND};

    WormBoss(IP& ip, Level& level);
    ~WormBoss();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void ChangeState(State state);

private:
    sf::Clock _timer;
    sf::Clock _stateTimer;
    State _curState;
    float _nextStateTime;
};

#endif // WORMBOSS_H_INCLUDED
