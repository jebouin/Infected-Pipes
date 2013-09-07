#include "Level.h"
#include "IP.h"
#include "Map.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "Pipe.h"
#include "Spawner.h"
#include "EntityManager.h"

Level::Level(IP& ip) {
    _levelImage = sf::Image(ip._textureLoader->GetImage("level"));
    _map = new Map(ip, sf::Vector2i(_levelImage.getSize()));
    _spawner = new Spawner(ip);
    for(int i=0 ; i<_levelImage.getSize().x ; i++) {
        for(int j=0 ; j<_levelImage.getSize().y ; j++) {
            sf::Vector2i pos(i, j);
            sf::Color c = _levelImage.getPixel(i, j);
            if(c == sf::Color(255, 255, 255, 0)) {
                _map->SetTile(pos, 0);
            } else if(c == sf::Color(122, 137, 60)) {
                _map->SetTile(pos, 1);
            } else if(c == sf::Color(104, 99, 46)) {
                _map->SetTile(pos, 2);
            } else {
                _map->SetTile(pos, 0);
            }

            if(c.r == 127 && c.g == 127 && c.b == 127 && c.a != 0) {
                Pipe *p = new Pipe(ip, sf::Vector2f(pos)*16.f, c.a*360.f/256.f);
                _spawner->AddPipe(p);
            }
        }
    }
}

Level::~Level() {
    delete _map;
    delete _spawner;
}

void Level::Update(IP& ip, EntityManager& eManager) {
    _spawner->Update(ip, eManager);
}

void Level::Draw(IP& ip) {
    _spawner->Draw(ip);
    _map->Draw(ip);
}

Map& Level::GetMap() {
    return *_map;
}

Spawner& Level::GetSpawner() {
    return *_spawner;
}
