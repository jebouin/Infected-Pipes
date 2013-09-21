#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class Renderer {
    public:
    Renderer(sf::Vector2i size);
    ~Renderer();
    void Clear();
    void Draw(const sf::Drawable& drawable);
    void DrawToWindow(sf::RenderWindow& window);
    sf::RenderTexture& GetTexture();

    public:
    sf::RenderTexture *_littleTexture;
    sf::RenderTexture *_bigTexture;
    sf::Sprite _littleSprite;
    sf::Sprite _bigSprite;
    sf::Shader _mosaicShader;
    sf::Vector2i _size;
};

#endif // RENDERER_H_INCLUDED
