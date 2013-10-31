#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Scene.h"

class IP;
class Map;
class Grass;
class Background;

class MainMenu : public Scene {
public:
    MainMenu(IP& ip);
    ~MainMenu();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);

private:
    Map *_map;
    Grass *_grass;
    Background *_background;
    sf::View *_view;
};

#endif //MAINMENU_H_INCLUDED
