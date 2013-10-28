#ifndef DUCK_H_INCLUDED
#define DUCK_H_INCLUDED

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

class Duck : public GameEntity {
    public:
    Duck(IP& ip);
    ~Duck();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager);
    void Draw(IP& ip);

    private:

};

#endif // DUCK_H_INCLUDED
