#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;

struct Flash {
    sf::Clock _timer;
    float _time;
    float _power;
};

class Renderer {
    public:
    Renderer(sf::Vector2i size);
    ~Renderer();
    void Clear();
    void Update(IP& ip, float eTime);
    void Draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default);
    void DrawToWindow(sf::RenderWindow& window, IP& ip);
    sf::RenderTexture& GetTexture();
    void AddFlash(float time, float power);

    public:
    sf::RenderTexture *_littleTexture;
    sf::RenderTexture *_bigTexture;
    sf::Sprite _littleSprite;
    sf::Sprite _bigSprite;
    sf::Shader _mosaicShader;
    sf::Vector2i _size;
    std::vector<Flash> _flashes;
};

#endif // RENDERER_H_INCLUDED
