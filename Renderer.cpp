#include "Renderer.h"

Renderer::Renderer(sf::Vector2i size) {
    _size = size;

    _littleTexture = new sf::RenderTexture();
    _littleTexture->create(size.x, size.y);
    _littleTexture->setSmooth(false);
    _bigTexture = new sf::RenderTexture();
    _bigTexture->create(size.x*4, size.y*4);
    _bigTexture->setSmooth(false);

    _littleSprite.setTexture(_littleTexture->getTexture());
    _littleSprite.scale(4, 4);
    _bigSprite.setTexture(_bigTexture->getTexture());

    if(!_mosaicShader.loadFromFile("shaders/mosaic.frag", sf::Shader::Fragment)) {
        cout << "Cannot load mosaic shader..." << endl;
    }
}

Renderer::~Renderer() {
    delete _littleTexture;
    delete _bigTexture;
}

void Renderer::Clear() {
    _littleTexture->clear(sf::Color(31, 23, 53));
    _bigTexture->clear();
}

void Renderer::Draw(const sf::Drawable& drawable, const sf::RenderStates &states) {
    _littleTexture->draw(drawable, states);
}

void Renderer::DrawToWindow(sf::RenderWindow& window) {
    _littleTexture->display();
    _bigTexture->draw(_littleSprite);
    _bigTexture->display();

    _mosaicShader.setParameter("texture", sf::Shader::CurrentTexture);
    _mosaicShader.setParameter("r", sf::Vector2f(_size*4));
    window.draw(_bigSprite, &_mosaicShader);
}

sf::RenderTexture& Renderer::GetTexture() {
    return *_littleTexture;
}
