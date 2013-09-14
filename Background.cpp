#include "Background.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"

Background::Background(IP& ip, string name, float zoom) {
    _back.setTexture(ip._textureLoader->GetTexture(name));
    _view = sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _zoom = zoom;
}

Background::~Background() {

}

void Background::Draw(IP& ip, sf::View& prevView) {
    _view = sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _view.setCenter(prevView.getCenter()*_zoom + sf::Vector2f(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y)/2.f);
    sf::RenderTexture& t(ip._renderer->GetTexture());
    t.setView(_view);
    for(int i=-1 ; i<2 ; i++) {
        for(int j=-1 ; j<2 ; j++) {
            _back.setPosition(sf::Vector2f(_back.getTextureRect().width*i, _back.getTextureRect().height*j));
            ip._renderer->Draw(_back);
        }
    }
    t.setView(prevView);
}
