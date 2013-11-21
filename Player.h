#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Character;
class EntityManager;
class Level;
class ParticleManager;
class BulletManager;
class GUI;
class Camera;

class Player {
    public:
    Player(IP& ip, EntityManager& eManager);
    ~Player();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    sf::View& GetView();
    Character& GetCharacter();
    //void SetView(sf::View v);

    private:
    Camera *_camera;
    Character *_character;
};

#endif // PLAYER_H_INCLUDED
