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

class Character : public GameEntity {
    public:
    Character(IP& ip);
    ~Character();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void EnterPipe(Level& level);
    bool EnteringPipe();
    void Hit(Ennemy *other, IP& ip, ParticleManager& pManager);
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
};

#endif // CHARACTER_H_INCLUDED
