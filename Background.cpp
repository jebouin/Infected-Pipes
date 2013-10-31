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
    _name = name;

    if(_name == "nightBackground") {
        for(int i=0 ; i<map.GetSize().x*2.5f ; i++) {
            if(rand()%3==0) {
                sf::Sprite fir;
                fir.setTexture(ip._textureLoader->GetTexture("fir"));
                fir.setPosition(sf::Vector2f(-1.25*16.f*map.GetSize().x, 0) + sf::Vector2f(sf::Vector2i(i, 9))*16.f + sf::Vector2f(0, -fir.getGlobalBounds().height + 16));
                _backSprites.push_back(fir);
            }
        }

        //!!! star density
        for(int i=0 ; i<100 ; i++) {
            int starType = rand()%4;
            sf::Sprite star;
            star.setTexture(ip._textureLoader->GetTexture("stars"));
            switch(starType) {
            case 0:
                star.setTextureRect(sf::IntRect(0, 0, 5, 5));
                break;
            case 1:
                star.setTextureRect(sf::IntRect(0, 5, 3, 3));
                break;
            case 2:
                star.setTextureRect(sf::IntRect(0, 8, 1, 1));
                break;
            case 3:
                star.setTextureRect(sf::IntRect(0, 9, 1, 1));
                break;
            }
            /*correct that!*/star.setPosition(MathHelper::RandInt(0, ip._renderer->GetTexture().getSize().x-star.getLocalBounds().width), MathHelper::RandInt(0, ip._renderer->GetTexture().getSize().y-star.getLocalBounds().height));
            star.setOrigin(sf::Vector2f(star.getTextureRect().width, star.getTextureRect().height)/2.f);
            _backSprites2.push_back(star);
        }

        sf::Sprite moon;
        moon.setTexture(ip._textureLoader->GetTexture("moon"));
        moon.setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/4.f*3.f, ip._renderer->GetTexture().getSize().y/4.f));
        _backSprites2.push_back(moon);
    }

    if(_name == "lavaBackground") {
        _back2.setTexture(ip._textureLoader->GetTexture("lavaBackground2"));
    }
}

Background::~Background() {

}

void Background::Update(IP& ip, float elapsedTime) {
    if(_name == "nightBackground") {
        static sf::IntRect tRects[4] = {sf::IntRect(0, 0, 5, 5), sf::IntRect(0, 5, 3, 3), sf::IntRect(0, 8, 1, 1), sf::IntRect(0, 9, 1, 1)};
        for(int i=0 ; i<100 ; i++) {
            if(rand()%3==0) {
                sf::Sprite& s(_backSprites2[i]);
                s.setTextureRect(tRects[rand()%2 + 2*(i%2)]);
                s.setOrigin(sf::Vector2f(s.getTextureRect().width, s.getTextureRect().height)/2.f);
            }
        }
    }
}

void Background::Draw(IP& ip, sf::View& prevView) {
    _view = sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _view.setCenter(prevView.getCenter()*_zoom + sf::Vector2f(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y)/2.f);
    sf::RenderTexture& t(ip._renderer->GetTexture());

    if(_name == "lavaBackground") {
        _view.setCenter(sf::Vector2f(_view.getCenter().x / 2.f, _view.getCenter().y / 2.f));
        t.setView(_view);
        sf::FloatRect r2 = MathHelper::View2Rect(_view);
        sf::IntRect tr2(_back2.getTextureRect());
        for(int i=r2.left/tr2.width-1 ; i<(r2.left+r2.width)/tr2.width+1 ; i++) {
            for(int j=r2.top/tr2.height-1 ; j<(r2.top+r2.height)/tr2.height+1 ; j++) {
                _back2.setPosition(sf::Vector2f(_back2.getTextureRect().width*i, _back2.getTextureRect().height*j));
                ip._renderer->Draw(_back2);
            }
        }
    }

    _view.setCenter(prevView.getCenter()*_zoom + sf::Vector2f(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y)/2.f);
    t.setView(_view);
    sf::FloatRect r = MathHelper::View2Rect(_view);
    sf::IntRect tr(_back.getTextureRect());
    for(int i=r.left/tr.width-1 ; i<(r.left+r.width)/tr.width+1 ; i++) {
        for(int j=r.top/tr.height-1 ; j<(r.top+r.height)/tr.height+1 ; j++) {
            _back.setPosition(sf::Vector2f(_back.getTextureRect().width*i, _back.getTextureRect().height*j));
            ip._renderer->Draw(_back);
        }
    }

    for(int i=0 ; i<_backSprites2.size() ; i++) {
        ip._renderer->Draw(_backSprites2[i]);
    }

    _view.setCenter(sf::Vector2f(prevView.getCenter().x / 2.5f, prevView.getCenter().y));
    t.setView(_view);
    for(int i=0 ; i<_backSprites.size() ; i++) {
        ip._renderer->Draw(_backSprites[i]);
    }

    t.setView(prevView);
}
