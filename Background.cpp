#include "Background.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "Level.h"
#include "Map.h"

Background::Background(IP& ip, string name, float zoom, Level& level) : _level(level){
    Map& map(level.GetMap());
    _back.setTexture(ip._textureLoader->GetTexture(name));
    _view = sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _zoom = zoom;

    if(name == "nightBackground") {
        for(int i=0 ; i<map.GetSize().x*2.5f ; i++) {
            if(rand()%3==0) {
                sf::Sprite fir;
                fir.setTexture(ip._textureLoader->GetTexture("fir"));
                fir.setPosition(sf::Vector2f(-1.25*16.f*map.GetSize().x, 0) + sf::Vector2f(sf::Vector2i(i, 9))*16.f + sf::Vector2f(0, -fir.getGlobalBounds().height + 16));
                _backSprites.push_back(fir);
            }
        }
    }
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

    _view.setCenter(sf::Vector2f(prevView.getCenter().x / 2.5f, prevView.getCenter().y));
    t.setView(_view);
    for(int i=0 ; i<_backSprites.size() ; i++) {
        ip._renderer->Draw(_backSprites[i]);
    }

    t.setView(prevView);
}
