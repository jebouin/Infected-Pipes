#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class TextureLoader;

class Cursor : public sf::Sprite {
    public:
    Cursor(IP& ip, TextureLoader& tLoader);
    ~Cursor();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    sf::Clock _inactiveTimer;
    sf::Vector2f _prevPos;
};

#endif // CURSOR_H_INCLUDED
