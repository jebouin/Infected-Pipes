#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

using namespace std;

class IP;
class Map;
class Level;
class EntityManager;
class ParticleManager;
class BulletManager;
class Ennemy;
class Weapon;
class Bow;

struct Arm {
    sf::IntRect _textureRect;
    sf::Vector2f _origin;
};

class Character : public GameEntity {
    public:
    enum ArmType {EMPTY, RAINBOW};

    Character(IP& ip);
    ~Character();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void LoadArm(ArmType t);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void EnterPipe(Level& level);
    bool EnteringPipe();
    void Hit(Ennemy *other, IP& ip, ParticleManager& pManager, Level& level);
    void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir);
    void EarnXP(int amount);
    void LevelUp();
    int GetXP() const;
    int GetNextXP() const;
    int GetLevel() const;

    private:
    int _level;
    int _xp;
    int _nextXP;
    bool _enteringPipe;
    bool _leavingPipe;
    sf::Clock _enterTimer;

    Weapon *_weapon;
    sf::Sprite _arm;

    map<ArmType, Arm> _arms;
};

#endif // CHARACTER_H_INCLUDED
