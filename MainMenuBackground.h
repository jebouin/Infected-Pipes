#ifndef MAINMENUBACKGROUND_H_INCLUDED
#define MAINMENUBACKGROUND_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;
class Grass;
class Background;

class MainMenuBackground {
public:
    MainMenuBackground(IP& ip);
    ~MainMenuBackground();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);

private:
    Map *_map;
    Grass *_grass;
    Background *_background;
    sf::View *_view;
    sf::RenderTexture *_rt;
    std::vector<sf::Sprite> _trees;
    std::vector<sf::Vector2f> _treePos;
    sf::Vector2u _ssize;
    sf::Sprite _forest;
    float _forestPosX;
    float _viewVelX;
    float _simViewX;
};

#endif // MAINMENUBACKGROUND_H_INCLUDED
