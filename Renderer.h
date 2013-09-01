#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Renderer {
    public:
    Renderer(sf::Vector2i size, int scale);
    ~Renderer();
    void Clear();
    void Draw(const sf::Drawable& drawable);
    void DrawToWindow(sf::RenderWindow& window);
    sf::RenderTexture& GetTexture();

    public:
    sf::RenderTexture *_texture;
    sf::Sprite _sprite;
    sf::Sprite _mosaic;
    sf::Texture _mosaicTex;
    sf::Vector2i _size;
    int _scale;
};

#endif // RENDERER_H_INCLUDED
