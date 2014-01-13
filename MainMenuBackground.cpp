#include "MainMenuBackground.h"
#include "IP.h"
#include "Map.h"
#include "Grass.h"
#include "Background.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "MathHelper.h"

MainMenuBackground::MainMenuBackground(IP& ip) {
    _ssize = ip._renderer->GetSize();
    _map = new Map(ip, sf::Vector2i(64, 2));
    for(int i=0 ; i<_map->GetSize().x ; i++) {
        _map->SetTile(sf::Vector2i(i, _map->GetSize().y-1), 1, Map::FRONT);
    }
    _grass = new Grass(ip, *_map);
    _view = new sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _view->setCenter(sf::Vector2f(_view->getCenter().x, _map->GetSize().y*16.f - _view->getSize().y/2.f));
    _view->setCenter(sf::Vector2f(sf::Vector2i(_view->getCenter())));
    _background = new Background(ip, "nightBackground", 0., *_map);
    _rt = new sf::RenderTexture();
    _rt->create(ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y);

    _simViewX = 0;
    _forestPosX = 0;
    //_viewVelX = .05f;
    _viewVelX = .15f;

    //add some trees
    for(int i=0 ; i<_ssize.x/42 ; i++) {
        sf::Sprite tree(ResourceLoader::GetTexture("fir"));
        tree.setOrigin(sf::Vector2f(tree.getTextureRect().width/2, tree.getTextureRect().height));
        tree.setPosition(sf::Vector2f(0, _ssize.y-15));
        _treePos.push_back(sf::Vector2f(MathHelper::RandFloat(0, _ssize.x), 0));
        _trees.push_back(tree);
    }
    _forest.setTexture(ResourceLoader::GetTexture("forestBackground"));
    _forest.setPosition(sf::Vector2f(0, _ssize.y-_forest.getTextureRect().height));
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
    delete _rt;
    _rt = 0;
}

void MainMenuBackground::Update(IP& ip, float eTime) {
    _view->move(eTime*_viewVelX, 0);
    _simViewX += _viewVelX*eTime;
    _grass->Update(ip);
    _background->Update(ip, eTime);
    for(int i=0 ; i<_trees.size() ; i++) {
        sf::Sprite& t(_trees[i]);
        sf::Vector2f& basePos(_treePos[i]);
        t.setPosition(sf::Vector2f(basePos.x - (_simViewX/2.f), t.getPosition().y));
        if(t.getPosition().x < -32) {
            t.setPosition(sf::Vector2f(_ssize.x+32, t.getPosition().y));
        }
        if(t.getPosition().x > _ssize.x+32) {
            t.setPosition(sf::Vector2f(-32, t.getPosition().y));
        }
        basePos.x = (_simViewX/2.f)+t.getPosition().x;
        t.setPosition(sf::Vector2f(sf::Vector2i(t.getPosition())));
    }
    _forestPosX += eTime*_viewVelX/-4.f;
}

void MainMenuBackground::Draw(IP& ip) {
    _rt->clear(sf::Color(0, 0, 0, 0));
    _rt->setView(_rt->getDefaultView());
    _map->DrawLayer(*_rt, Map::BACK);
    _map->DrawLayer(*_rt, Map::FRONT);
    _grass->Draw(*_rt);
    _rt->display();

    _background->Draw(ip._renderer->GetTexture(), *_view);

    ip._renderer->GetTexture().setView(ip._renderer->GetTexture().getDefaultView());
    //forest/mountain
    if(_forestPosX+_forest.getTextureRect().width < _ssize.x) {
        _forestPosX += _forest.getTextureRect().width;
    }
    _forest.setPosition(sf::Vector2f(_forestPosX, _forest.getPosition().y));
    ip._renderer->Draw(_forest);
    _forest.setPosition(_forest.getPosition() + sf::Vector2f(-_forest.getTextureRect().width, 0));
    ip._renderer->Draw(_forest);
    //trees
    for(int i=0 ; i<_trees.size() ; i++) {
        ip._renderer->Draw(_trees[i]);
    }
    ip._renderer->GetTexture().setView(*_view);

    if(_view->getCenter().x+_view->getSize().x/2.f >= 1024) {
        sf::Sprite loopSprite;
        loopSprite.setTexture(_rt->getTexture());
        loopSprite.setPosition(sf::Vector2f(1024, 1));
        ip._renderer->Draw(loopSprite);
    }
    if(_view->getCenter().x-_view->getSize().x/2.f >= 1024) {
        _view->setCenter(sf::Vector2f(_view->getSize().x/2.f, _view->getCenter().y));
    }

    _map->DrawLayer(ip._renderer->GetTexture(), Map::BACK);
    _map->DrawLayer(ip._renderer->GetTexture(), Map::FRONT);
    _grass->Draw(ip._renderer->GetTexture());
}
