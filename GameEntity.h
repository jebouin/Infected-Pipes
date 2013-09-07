#ifndef GAMEENTITY_H_INCLUDED
#define GAMEENTITY_H_INCLUDED

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

using namespace std;

class IP;
class Level;
class Map;
class EntityManager;

class GameEntity : public MovingSprite {
    public:
    GameEntity(IP& ip, string name, sf::IntRect hitbox, int hp);
    ~GameEntity();
    void Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager);
    void Update(IP& ip, float elapsedTime);
    void Collide(GameEntity* other);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void Jump(Level& level);
    void Damage(int dmg);
    void Hit(GameEntity *other);
    void SetJumpPower(float p);
    void SetSpeed(float s);
    void SetWeight(float w);
    float GetWeight();
    bool IsAlive();
    int GetHp();
    int GetHpMax();

    private:
    float _jumpPower;
    float _speed;
    float _weight;
    bool _alive;
    int _hpMax;
    int _hp;
};

#endif // GAMEENTITY_H_INCLUDED
