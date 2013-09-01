#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class GameEntity;
class IP;
class Map;

class EntityManager {
    public:
    EntityManager();
    ~EntityManager();
    void Update(IP& ip, float eTime, Map& map);
    void Draw(IP& ip);
    void Add(GameEntity *entity);
    int GetNbEntities();
    GameEntity& GetEntity(int id);

    private:
    vector<GameEntity*> _entities;
};

#endif // ENTITYMANAGER_H_INCLUDED
