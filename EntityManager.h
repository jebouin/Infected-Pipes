#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;
class Ennemy;
class Character;
class ParticleManager;
class BulletManager;

class EntityManager {
    public:
    EntityManager();
    ~EntityManager();
    void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Add(Ennemy *e);
    void Clear();
    int GetNbEnnemies();
    Ennemy* GetEnnemy(int id);

    private:
    vector<Ennemy*> _ennemies;
};

#endif // ENTITYMANAGER_H_INCLUDED
