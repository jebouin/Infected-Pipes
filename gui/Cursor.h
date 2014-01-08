#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;

class Cursor : public sf::Sprite {
    public:
    Cursor(IP& ip);
    ~Cursor();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    sf::Clock _inactiveTimer;
    sf::Vector2f _prevPos;
};

#endif // CURSOR_H_INCLUDED
