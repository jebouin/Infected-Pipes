#ifndef SIGHT_H_INCLUDED
#define SIGHT_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;

class Sight {
    public:
    Sight(IP& ip);
    ~Sight();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    sf::Clock _timer;
    sf::VertexArray _lines;
};

#endif // SIGHT_H_INCLUDED
