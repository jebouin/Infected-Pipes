#ifndef CHESTOPENED_H_INCLUDED
#define CHESTOPENED_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;

class ChestOpened {
    public:
    ChestOpened(IP& ip);
    ~ChestOpened();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);

    private:
    sf::Clock _timer;
    sf::Texture _texture;
    sf::RenderTexture _rTexture;
    sf::Sprite _sprite;
    sf::Sprite _fSprite;
    sf::Shader _shader;
};

#endif // CHESTOPENED_H_INCLUDED
