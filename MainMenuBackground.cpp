#include "MainMenuBackground.h"
#include "IP.h"
#include "Map.h"
#include "Grass.h"
#include "Background.h"
#include "Renderer.h"
#include "TextureLoader.h"

MainMenuBackground::MainMenuBackground(IP& ip) {
    _map = new Map(ip, sf::Vector2i(64, 2));
    for(int i=0 ; i<_map->GetSize().x ; i++) {
        _map->SetTile(sf::Vector2i(i, _map->GetSize().y-1), 1, Map::FRONT);
    }
    _grass = new Grass(ip, *_map);
    _view = new sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _view->setCenter(sf::Vector2f(_view->getCenter().x, _map->GetSize().y*16.f - _view->getSize().y/2.f));
    _view->setCenter(sf::Vector2f(sf::Vector2i(_view->getCenter())));
    _background = new Background(ip, "nightBackground", 0., *_map);
}

MainMenuBackground::~MainMenuBackground() {
    delete _map;
    _map = 0;
    delete _grass;
    _grass = 0;
    delete _background;
    _background = 0;
    delete _view;
    _view = 0;
}

void MainMenuBackground::Update(IP& ip, float eTime) {
    _view->move(eTime*0.02f, 0);
    _grass->Update(ip);
    _background->Update(ip, eTime);
}

void MainMenuBackground::Draw(IP& ip) {
    ip._renderer->GetTexture().setView(*_view);
    _background->Draw(ip, *_view);
    _map->DrawLayer(ip, Map::BACK);
    _map->DrawLayer(ip, Map::FRONT);
    _grass->Draw(ip);
}
