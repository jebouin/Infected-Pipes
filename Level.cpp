#include "Level.h"
#include "IP.h"
#include "Map.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "Pipe.h"
#include "Spawner.h"
#include "EntityManager.h"
#include "Background.h"
#include "Grass.h"

Level::Level(IP& ip) {
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground"};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "nightBackground"};
    Load(ip, "intro");
}

Level::~Level() {
    delete _map;
    delete _spawner;
    delete _grass;
    delete _background;
}

void Level::Update(IP& ip, EntityManager& eManager) {
    _spawner->Update(ip, eManager);
    _grass->Update(ip);
}

void Level::DrawBack(IP& ip, sf::View& prevView) {
    _background->Draw(ip, prevView);
}

void Level::DrawFront(IP& ip) {
    _spawner->Draw(ip);
    _map->Draw(ip);
    _grass->Draw(ip);
}

Map& Level::GetMap() {
    return *_map;
}

Spawner& Level::GetSpawner() {
    return *_spawner;
}

void Level::Load(IP& ip, string name) {
    LevelInfo& info(_levelInfos[name]);
    _levelImage = sf::Image(ip._textureLoader->GetImage(info._imageName));
    _map = new Map(ip, sf::Vector2i(_levelImage.getSize()));
    _spawner = new Spawner(ip);
    for(int i=0 ; i<_levelImage.getSize().x ; i++) {
        for(int j=0 ; j<_levelImage.getSize().y ; j++) {
            sf::Vector2i pos(i, j);
            sf::Color c = _levelImage.getPixel(i, j);
            if(c == sf::Color(0, 0, 0, 0)) {
                _map->SetTile(pos, 0);
            } else if(c == sf::Color(122, 137, 60)) {
                _map->SetTile(pos, 1);
            } else if(c == sf::Color(80, 80, 80)) {
                _map->SetTile(pos, 2);
            } else if(c == sf::Color(85, 85, 85)) {
                _map->SetTile(pos, 3);
            } else {
                _map->SetTile(pos, 0);
            }

            if(c.r == 127 && c.g == 127 && c.b == 127 && c.a != 0) {
                Pipe *p = new Pipe(ip, sf::Vector2f(pos)*16.f, c.a*360.f/256.f);
                _spawner->AddPipe(p);
            }
        }
    }
    _background = new Background(ip, _levelInfos[name]._backgroundName);
    _grass = new Grass(ip, *this);
}
