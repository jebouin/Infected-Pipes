#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

using namespace std;

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;
class MovingSprite;

class Boss : public Ennemy {
public:
    Boss(IP& ip, string name, sf::IntRect hitbox, int hp, int xp, int incDifficulty, Level& level);
    ~Boss();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void AddPart(MovingSprite* part);
    void ClearParts();
    int GetNbParts();
    MovingSprite* GetPart(int id);

private:
    vector<MovingSprite*> _parts;
};

#endif // BOSS_H_INCLUDED
