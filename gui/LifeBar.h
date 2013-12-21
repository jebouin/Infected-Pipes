#ifndef LIFEBAR_H_INCLUDED
#define LIFEBAR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Character;

class LifeBar : public sf::Sprite {
    public:
    LifeBar(IP& ip, Character& character);
    ~LifeBar();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    const Character& _character;
    sf::Sprite _bar;
    sf::Text _text;
};

#endif // LIFEBAR_H_INCLUDED
