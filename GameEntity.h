#ifndef GAMEENTITY_H_INCLUDED
#define GAMEENTITY_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

using namespace std;

class IP;
class Map;

class GameEntity : public MovingSprite {
    public:
    GameEntity(IP& ip, string name);
    ~GameEntity();
    void Update(IP& ip, float elapsedTime, Map& map);
    void GoLeft(float eTime);
    void GoRight(float eTime);
    void Jump(Map& map);

    private:
    float _jumpPower;
    float _speed;
};

#endif // GAMEENTITY_H_INCLUDED
