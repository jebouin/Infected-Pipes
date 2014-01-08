#ifndef SKULL_H_INCLUDED
#define SKULL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Skull : public GameEntity {
    public:
    Skull(IP& ip);
    ~Skull();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager);
    void Draw(IP& ip);

    private:

};

#endif // SKULL_H_INCLUDED
