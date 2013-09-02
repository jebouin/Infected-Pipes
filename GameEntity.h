#ifndef GAMEENTITY_H_INCLUDED
#define GAMEENTITY_H_INCLUDED

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

using namespace std;

class IP;
class Map;
class EntityManager;

class GameEntity : public MovingSprite {
    public:
    GameEntity(IP& ip, string name, sf::IntRect hitbox);
    ~GameEntity();
    void Update(IP& ip, float elapsedTime, Map& map, EntityManager& eManager);
    void Collide(GameEntity* other);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void Jump(Map& map);
    void SetJumpPower(float p);
    void SetSpeed(float s);
    void SetWeight(float w);
    float GetWeight();

    private:
    float _jumpPower;
    float _speed;
    float _weight;
};

#endif // GAMEENTITY_H_INCLUDED
