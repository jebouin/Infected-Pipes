#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class LifeBar;
class TextureLoader;
class Character;
class XPBar;

class GUI {
    public:
    GUI(IP& ip, TextureLoader& tLoader, Character& character);
    ~GUI();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    LifeBar *_lifeBar;
    XPBar *_xpBar;
};

#endif // GUI_H_INCLUDED
