#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;

class Background {
    public:
    Background(IP& ip, string name, float zoom, Level& level);
    ~Background();
    void Draw(IP& ip, sf::View& prevView);

    private:
    vector<sf::Sprite> _backSprites;
    vector<sf::Sprite> _backSprites2;
    sf::Sprite _back;
    sf::View _view;
    float _zoom;

    const Level& _level;
};

#endif // BACKGROUND_H_INCLUDED
