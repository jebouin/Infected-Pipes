#ifndef WORMBOSS_H_INCLUDED
#define WORMBOSS_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class WormBoss : public Ennemy {
public:
    enum State {IDLE, PREPARING, JUMPING, GOINGUP, GOINGDOWN, INGROUND, DYING};

    WormBoss(IP& ip, Level& level);
    ~WormBoss();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void ChangeState(State state);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void ExplodeParticles(IP& ip, ParticleManager& pManager, sf::Vector2f pos);

private:
    sf::Clock _timer;
    sf::Clock _stateTimer;
    sf::Clock _particleTimer;
    sf::Clock _attackTimer;
    sf::Clock _explodeTimer;
    State _curState;
    float _nextStateTime;
    int _nbPartsExploded;

    std::vector<MovingSprite*> _parts;
};

#endif // WORMBOSS_H_INCLUDED
