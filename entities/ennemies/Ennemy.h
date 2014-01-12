#ifndef ENNEMY_H_INCLUDED
#define ENNEMY_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Ennemy : public GameEntity {
    public:
    enum EnnemyType {SPIDEROCK, ROCKWORM, BAT, SNAIL, SLIME, SLIMEY, SNOWBALL};

    Ennemy(IP& ip, std::string name, sf::IntRect hitbox, int hpn, int xp, int incDifficulty, Level& level);
    virtual ~Ennemy();
    virtual void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    virtual void Draw(IP& ip);
    int GetXP();
    int GetIncDifficulty();
    virtual void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level);
    virtual void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    bool _inPipe;
    int _xp;
    int _incDifficulty;
    Level& _level;
    Character* _character;
};

#endif // ENNEMY_H_INCLUDED
