#include "Background.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"

Background::Background(IP& ip, string name) {
    _back.setTexture(ip._textureLoader->GetTexture(name));
    _view = sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
}

Background::~Background() {

}

void Background::Draw(IP& ip, sf::View& prevView) {
    /*float scrollFact = 6.f;
    _view.setCenter(sf::Vector2f(prevView.getCenter().x/scrollFact, prevView.getCenter().y));
    _back.setPosition(-prevView.getSize().x/scrollFact - 57, 0);*/
    sf::RenderTexture& t(ip._renderer->GetTexture());
    t.setView(_view);
    ip._renderer->Draw(_back);
    t.setView(prevView);
}
