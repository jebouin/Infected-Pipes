#include "ChestOpened.h"
#include "IP.h"
#include "MathHelper.h"
#include "Renderer.h"

ChestOpened::ChestOpened(IP& ip) {
    _texture.create(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y);
    _rTexture.create(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y);
    _rTexture.setSmooth(false);
    _texture.setSmooth(false);

    if(!_shader.loadFromFile("shaders/chestOpened.frag", sf::Shader::Fragment)) {
        std::cout << "Cannot load chest opened shader..." << std::endl;
    }

    _sprite.setTexture(_texture);
    _fSprite.setTexture(_rTexture.getTexture());
}

ChestOpened::~ChestOpened() {

}

void ChestOpened::Update(IP& ip, float eTime) {

}

void ChestOpened::Draw(IP& ip) {
    Renderer& r(*ip._renderer);
    sf::View pv(r.GetTexture().getView());

    _shader.setParameter("texture", ip._renderer->GetTexture().getTexture());
    _shader.setParameter("r", sf::Vector2f(_texture.getSize()));
    _shader.setParameter("time", float(_timer.getElapsedTime().asSeconds()));

    r.GetTexture().setView(r.GetTexture().getDefaultView());

    _rTexture.clear();
    _rTexture.draw(_sprite, &_shader);
    _rTexture.display();

    ip._renderer->Draw(_fSprite);
    r.GetTexture().setView(pv);
}
