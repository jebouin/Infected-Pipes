#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Scene.h"

class IP;
class MainMenuBackground;

class MainMenu : public Scene {
public:
    MainMenu(IP& ip);
    ~MainMenu();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);

private:
    sf::Sprite _title;
    MainMenuBackground *_background;
};

#endif //MAINMENU_H_INCLUDED
