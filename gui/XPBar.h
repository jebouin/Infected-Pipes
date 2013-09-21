#ifndef XPBAR_H_INCLUDED
#define XPBAR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Character;
class TextureLoader;

class XPBar : public sf::Sprite {
    public:
    XPBar(IP& ip, Character& character, TextureLoader& tLoader);
    ~XPBar();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    const Character& _character;
    sf::Sprite _bar;
};

#endif // XPBAR_H_INCLUDED
