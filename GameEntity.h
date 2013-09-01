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

    private:

};

#endif // GAMEENTITY_H_INCLUDED
