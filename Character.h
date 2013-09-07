#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

using namespace std;

class IP;
class Map;
class Level;
class EntityManager;

class Character : public GameEntity {
    public:
    Character(IP& ip);
    ~Character();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager);

    private:

};

#endif // CHARACTER_H_INCLUDED
