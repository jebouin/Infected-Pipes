#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Scene.h"

class IP;
class Level;
class EntityManager;
class Player;
class Background;
class ParticleManager;
class GUI;
class BulletManager;

class Game : public Scene {
public:
    Game(IP& ip);
    ~Game();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);

private:
    Level *_level;
    EntityManager *_entityManager;
    BulletManager *_bulletManager;
    Player *_player;
    ParticleManager *_particleManager;
    GUI *_gui;
};

#endif
