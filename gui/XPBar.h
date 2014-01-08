#ifndef XPBAR_H_INCLUDED
#define XPBAR_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class Character;

class XPBar : public sf::Sprite {
    public:
    XPBar(IP& ip, Character& character);
    ~XPBar();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    const Character& _character;
    sf::Sprite _bar;
};

#endif // XPBAR_H_INCLUDED
