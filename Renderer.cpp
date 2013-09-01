#include "Renderer.h"

Renderer::Renderer(sf::Vector2i size, int scale) {
    _size = size;
    _scale = scale;
    _texture = new sf::RenderTexture();
    _texture->create(size.x, size.y);
    _texture->setSmooth(false);

    //make mosaic
    sf::Uint8 *pixels = new sf::Uint8[scale*scale*4];
    for(int i=0 ; i<scale*scale ; i++) {
        for(int j=0 ; j<3 ; j++) {
            pixels[i*4+j] = 255;
        }
        pixels[i*4+3] = 0;
    }
    pixels[4+3] = 16;
    pixels[8+3] = 16;
    /*int max = 40;
    for(int i=0 ; i<scale ; i++) {
        int a = max-(i*max/scale);
        pixels[i*4+3] = a;
        pixels[(i*scale)*4+3] = a;
    }*/
    _mosaicTex.setSmooth(false);
    _mosaicTex.create(scale, scale);
    _mosaicTex.update(pixels);
    _mosaicTex.setRepeated(true);
    delete [] pixels;
    _mosaic.setTexture(_mosaicTex);
    _mosaic.setTextureRect(sf::IntRect(0, 0, size.x*scale, size.y*scale));

    _sprite.setTexture(_texture->getTexture());
    _sprite.scale(_scale, _scale);
}

Renderer::~Renderer() {
    delete _texture;
}

void Renderer::Clear() {
    _texture->clear(sf::Color(31, 23, 53));
}

void Renderer::Draw(const sf::Drawable& drawable) {
    _texture->draw(drawable);
}

void Renderer::DrawToWindow(sf::RenderWindow& window) {
    _texture->display();
    window.draw(_sprite);
    window.draw(_mosaic);
}

sf::RenderTexture& Renderer::GetTexture() {
    return *_texture;
}
