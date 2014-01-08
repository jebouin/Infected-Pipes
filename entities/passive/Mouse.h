#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Mouse : public GameEntity {
    public:
    Mouse(IP& ip);
    ~Mouse();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager);
    void Draw(IP& ip);
    void NewAction();

    private:
    bool _direction;
    float _actionTime;
    bool _curAction;
    sf::Clock _actionTimer;
};

#endif // MOUSE_H_INCLUDED
