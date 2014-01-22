#ifndef PAUSEMENU_H_INCLUDED
#define PAUSEMENU_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Scene.h"

using namespace std;

class IP;

class PauseMenu : public Scene {
public:
    PauseMenu(IP& ip);
    ~PauseMenu();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);

private:
    sf::Clock _timer;
    sf::ConvexShape _back;
    sf::View _view;
    bool _prevEscapePressed;
    sf::Vector2f _ssize;
    const sf::Color _baseColor;
    const sf::Color _selecColor;

    sf::Text _pause;
    sf::Text _resume;
    sf::Text _options;
    sf::Text _quit;
};

#endif //PAUSEMENU_H_INCLUDED
