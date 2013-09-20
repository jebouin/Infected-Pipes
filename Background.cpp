#include "Background.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "MathHelper.h"

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
    sf::FloatRect r = MathHelper::View2Rect(_view);
    sf::IntRect tr(_back.getTextureRect());
    for(int i=r.left/tr.width-1 ; i<(r.left+r.width)/tr.width+1 ; i++) {
        for(int j=r.top/tr.height-1 ; j<(r.top+r.height)/tr.height+1 ; j++) {
            _back.setPosition(sf::Vector2f(_back.getTextureRect().width*i, _back.getTextureRect().height*j));
            ip._renderer->Draw(_back);
        }
    }
    t.setView(prevView);
}
