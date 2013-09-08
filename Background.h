#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;

class Background {
    public:
    Background(IP& ip, string name);
    ~Background();
    void Draw(IP& ip, sf::View& prevView);

    private:
    sf::Sprite _back;
    sf::View _view;
};

#endif // BACKGROUND_H_INCLUDED
