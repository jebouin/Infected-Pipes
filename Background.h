#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;

class Background {
    public:
    Background(IP& ip, string name, float zoom, Map& map);
    ~Background();
    void Update(IP& ip, float elapsedTime);
    void Draw(IP& ip, const sf::View& prevView);

    private:
    string _name;
    vector<sf::Sprite> _backSprites;
    vector<sf::Sprite> _backSprites2;
    sf::Sprite _back;
    sf::Sprite _back2;
    sf::View _view;
    float _zoom;

    //const Level& _level;
};

#endif // BACKGROUND_H_INCLUDED
