#ifndef GAMEENTITY_H_INCLUDED
#define GAMEENTITY_H_INCLUDED

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
    GameEntity(IP& ip, std::string name, sf::IntRect hitbox, int hp);
    virtual ~GameEntity();
    virtual void Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager, ParticleManager& pManager);
    virtual void Update(IP& ip, float elapsedTime);
    void Draw(IP& ip);
    void Collide(GameEntity* other, float elapsedTime);
    virtual void GoLeft(float eTime);
    virtual void GoRight(float eTime);
    void ChangeDir();
    void PlatformDrop(Level& level);
    bool Jump(Level& level);
    virtual void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level);
    virtual void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    virtual void Hit(GameEntity *other, IP& ip, ParticleManager& pManager, sf::Color color, int damage, EntityManager& eManager, Level& level);
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
    void SetPhysics(bool p);
    float GetSpeed();
    float GetWeight();
    bool IsAlive();
    int GetHP() const;
    int GetHPMax() const;
    bool GetDir();
    bool IsPushable();
    bool IsInvincible();
    bool HasPhysics() const;
    void SetWaterFriction(float f);
    void ResetHitShader();

    bool _inWater;

    protected:
    sf::Shader _hitShader;
    float _hitShaderAmp;

    private:
    sf::Clock _hitTimer;
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
    bool _havePhysics;
    int _hpMax;
    int _hp;
    float _waterFriction;
    float _lastTimeHit;
};

#endif // GAMEENTITY_H_INCLUDED
