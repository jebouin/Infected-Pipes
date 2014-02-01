#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

class IP;
class Map;
class Level;
class EntityManager;
class ParticleManager;
class BulletManager;
class Ennemy;
class Weapon;
class Bow;
class GUI;
class Player;
class HealingFly;

struct Arm {
    sf::IntRect _textureRect;
    sf::Vector2f _origin;
    sf::Vector2f _bulletPos;
    float _onPipeRotation;
};

class Character : public GameEntity {
    public:
    enum ArmType {EMPTY, RAINBOW, BOW, SHOTGUN, MACHINEGUN, RIFLE, ELECTRICGUN};

    Character(IP& ip);
    virtual ~Character();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager, Player& player);
    void Draw(IP& ip);
    void DrawFront(IP& ip);
    void LoadArm(ArmType t);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void Jump(Level& level, float eTime);
    void StopJumping();
    void EnterPipe(Level& level);
    void LeavePipe();
    bool EnteringPipe();
    void Hit(Ennemy *other, IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level);
    void EarnXP(int amount);
    void LevelUp();
    int GetXP() const;
    int GetNextXP() const;
    int GetLevel() const;
    void SetHPMultiplier(float mult);
    void SetSpeedMultiplier(float mult);
    void SetRegen(float regen);
    void SetJumpMultiplier(float mult);
    void SetReloadSpeedMultiplier(float mult);
    void SetDamageMultiplier(float mult);
    void SetGroundAttackLevel(int lvl);
    void AddFlies(IP& ip, int nb);
    int GetNbFlies();
    void Heal(IP& ip, ParticleManager& pManager, float amount);

    private:
    int _level;
    int _xp;
    int _nextXP;
    bool _enteringPipe;
    bool _leavingPipe;
    bool _canContinueJump;
    sf::Clock _enterTimer;
    sf::Clock _regenTimer;
    sf::Clock _groundAttackTimer;
    sf::Clock _bubbleTimer;
    float _bubbleTime;
    ArmType _curArmType;
    float _prevVelY;

    //skills
    float _baseHP;
    float _hpMult;
    float _baseSpeed;
    float _regen;
    float _baseJump;
    int _groundAttackLevel;
    vector<HealingFly*> _flies;

    Weapon *_weapon;
    sf::Sprite _arm;

    std::map<ArmType, Arm> _arms;
};

#endif // CHARACTER_H_INCLUDED
