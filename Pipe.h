#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;
class EntityManager;

class Pipe : public sf::Sprite{
    public:
    Pipe(IP& ip, sf::Vector2f pos);
    ~Pipe();
    void Update(IP& ip, EntityManager& eManager);
    void Spawn(IP& ip, EntityManager& eManager);

    private:
    sf::Clock c;
};

#endif // PIPE_H_INCLUDED
