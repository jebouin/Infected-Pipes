#ifndef GAMEENTITY_H_INCLUDED
#define GAMEENTITY_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

using namespace std;

class IP;
class Level;
class Map;
class EntityManager;
class ParticleManager;

class GameEntity : public MovingSprite {
    public:
    GameEntity(IP& ip, string name, sf::IntRect hitbox, int hp);
    ~GameEntity();
    void Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager, ParticleManager& pManager);
    void Update(IP& ip, float elapsedTime);
    void Collide(GameEntity* other, float elapsedTime);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void ChangeDir();
    void Jump(Level& level);
    void Damage(int dmg, IP& ip, ParticleManager& pManager);
    void Hit(GameEntity *other, IP& ip, ParticleManager& pManager);
    void SetJumpPower(float p);
    void SetSpeed(float s);
    void SetWeight(float w);
    void SetPushable(bool p);
    float GetWeight();
    bool IsAlive();
    int GetHp();
    int GetHpMax();
    bool GetDir();
    bool IsPushable();

    private:
    bool _dir;
    float _jumpPower;
    float _speed;
    float _weight;
    bool _alive;
    bool _pushable;
    int _hpMax;
    int _hp;

    sf::Vector2f _prevPos;
};

#endif // GAMEENTITY_H_INCLUDED
