#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class Level;

class Grass {
    public:
    Grass(IP& ip, Level& level);
    ~Grass();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    sf::Clock _timer;
    sf::VertexArray _grass;
};

#endif // GRASS_H_INCLUDED
