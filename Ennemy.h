#ifndef ENNEMY_H_INCLUDED
#define ENNEMY_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameEntity.h"

using namespace std;

class IP;
class Map;
class Character;
class EntityManager;

class Ennemy : public GameEntity {
    public:
    Ennemy(IP& ip);
    ~Ennemy();
    void Update(IP& ip, float eTime, Map& map, Character& character, EntityManager& eManager);

    private:

};

#endif // ENNEMY_H_INCLUDED
