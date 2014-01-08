#include "Renderer.h"
#include "IP.h"

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
        std::cout << "Cannot load mosaic shader..." << std::endl;
    }
}

Renderer::~Renderer() {
    delete _littleTexture;
    _littleTexture = 0;
    delete _bigTexture;
    _bigTexture = 0;
}

void Renderer::Clear() {
    _littleTexture->clear(sf::Color(0, 0, 0));
    _bigTexture->clear();
}

void Renderer::Update(IP& ip, float eTime) {
    for(int i=0 ; i<_flashes.size() ; i++) {
        float time = _flashes[i]._timer.getElapsedTime().asMilliseconds();
        if(time >= _flashes[i]._time) {
            _flashes.erase(_flashes.begin() + i);
        }
    }
}

void Renderer::Draw(const sf::Drawable& drawable, const sf::RenderStates &states) {
    _littleTexture->draw(drawable, states);
}

void Renderer::DrawToWindow(sf::RenderWindow& window, IP& ip) {
    _littleTexture->display();
    _bigTexture->draw(_littleSprite);
    _bigTexture->display();

    float totAmp = 0.;
    for(int i=0 ; i<_flashes.size() ; i++) {
        float curTime = _flashes[i]._timer.getElapsedTime().asMilliseconds();
        float curAmp = (1.-curTime/_flashes[i]._time)*_flashes[i]._power;
        totAmp += curAmp;
    }
    _mosaicShader.setParameter("texture", sf::Shader::CurrentTexture);
    _mosaicShader.setParameter("r", sf::Vector2f(_size*4));
    _mosaicShader.setParameter("amp", totAmp);
    window.draw(_bigSprite, &_mosaicShader);
}

sf::RenderTexture& Renderer::GetTexture() {
    return *_littleTexture;
}

void Renderer::AddFlash(float time, float power) {
    _flashes.push_back(Flash{sf::Clock(), time, power});
}

sf::Vector2u Renderer::GetSize() {
    return _littleTexture->getSize();
}
