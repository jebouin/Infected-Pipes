#include "Level.h"
#include "IP.h"
#include "Map.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "Pipe.h"
#include "EntityManager.h"

Level::Level(IP& ip) {
    _levelImage = sf::Image(ip._textureLoader->GetImage("level"));
    _map = new Map(ip, sf::Vector2i(_levelImage.getSize()));
    for(int i=0 ; i<_levelImage.getSize().x ; i++) {
        for(int j=0 ; j<_levelImage.getSize().y ; j++) {
            sf::Vector2i pos(i, j);
            sf::Color c = _levelImage.getPixel(i, j);
            if(c == sf::Color(0, 0, 0)) {
                _map->SetTile(pos, 0);
            } else if(c == sf::Color(122, 137, 60)) {
                _map->SetTile(pos, 1);
            } else if(c == sf::Color(104, 99, 46)) {
                _map->SetTile(pos, 2);
            }
        }
    }

    _pipe = new Pipe(ip, sf::Vector2f(_map->GetSize().x*16-48, _map->GetSize().y*16-48));
}

Level::~Level() {
    delete _map;
    delete _pipe;
}

void Level::Update(IP& ip, EntityManager& eManager) {
    _pipe->Update(ip, eManager);
}

void Level::Draw(IP& ip) {
    ip._renderer->Draw(*_pipe);
    _map->Draw(ip);
}

Map& Level::GetMap() {
    return *_map;
}
