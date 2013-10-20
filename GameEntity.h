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
    void Draw(IP& ip);
    void Collide(GameEntity* other, float elapsedTime);
    virtual void GoLeft(float eTime);
    virtual void GoRight(float eTime);
    void ChangeDir();
    void PlatformDrop(Level& level);
    void Jump(Level& level);
    virtual void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir);
    virtual void Die(IP& ip, ParticleManager& pManager);
    void Hit(GameEntity *other, IP& ip, ParticleManager& pManager, sf::Color color, int damage);
    void SetJumpPower(float p);
    void SetSpeed(float s);
    void SetWeight(float w);
    void SetPushable(bool p);
    void SetFlying(bool f);
    void SetHP(int hp);
    void SetHPMax(int max);
    void SetAlive(bool a);
    void SetInvincible(bool i);
    void SetAutoDir(bool a);
    void SetFriction(float friction);
    float GetSpeed();
    float GetWeight();
    bool IsAlive();
    int GetHP() const;
    int GetHPMax() const;
    bool GetDir();
    bool IsPushable();
    bool IsInvincible();

    protected:
    bool _inWater;

    private:
    bool _dir;
    float _jumpPower;
    float _speed;
    float _weight;
    float _friction;
    bool _alive;
    bool _pushable;
    bool _flying;
    bool _invincible;
    bool _autoDir;
    int _hpMax;
    int _hp;
};

#endif // GAMEENTITY_H_INCLUDED
