#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;
class EntityManager;
class Ennemy;

class Pipe : public sf::Sprite {
    public:
    Pipe(IP& ip, sf::Vector2f pos, float angle);
    ~Pipe();
    void Update(IP& ip, EntityManager& eManager);
    void Spawn(IP& ip, EntityManager& eManager, Ennemy *e);

    private:

};

#endif // PIPE_H_INCLUDED
