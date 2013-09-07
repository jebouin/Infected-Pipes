#ifndef SPAWNER_H_INCLUDED
#define SPAWNER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class Pipe;
class IP;
class EntityManager;
class MovingSprite;

class Spawner {
    public:
    Spawner(IP& ip);
    ~Spawner();
    void Update(IP& ip, EntityManager& eManager);
    void Draw(IP& ip);
    void AddPipe(Pipe *p);
    bool IsCollided(sf::FloatRect rect);
    bool IsCollided(MovingSprite& sprite, sf::Vector2f pos);
    bool IsCollided(MovingSprite& sprite);
    bool IsOnGround(MovingSprite& sprite);

    private:
    vector<Pipe*> _pipes;
};

#endif // SPAWNER_H_INCLUDED
