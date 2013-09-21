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
#include "Character.h"

Level::Level(IP& ip, Character& character) {
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground", 0.0001f};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "rockyBackground", 0.2f};
    _levelInfos["rockyCave2"] = LevelInfo{"level2", "rockyBackground", 0.2f};
    Load(ip, "intro", character);
}

Level::~Level() {
    delete _map;
    delete _spawner;
    delete _grass;
    delete _background;
}

void Level::Update(IP& ip, EntityManager& eManager, Character& character) {
    _spawner->Update(ip, eManager, *this, character);
    _grass->Update(ip);
}

void Level::DrawBack(IP& ip, sf::View& prevView) {
    _background->Draw(ip, prevView);
}

void Level::DrawFront(IP& ip) {
    _spawner->Draw(ip);
    _map->Draw(ip);
    //_grass->Draw(ip);
}

Map& Level::GetMap() {
    return *_map;
}

Spawner& Level::GetSpawner() {
    return *_spawner;
}

void Level::Load(IP& ip, string name, Character& character) {
    _curLevel = name;
    LevelInfo& info(_levelInfos[name]);
    _levelImage = sf::Image(ip._textureLoader->GetImage(info._imageName));
    _map = new Map(ip, sf::Vector2i(_levelImage.getSize()));
    _spawner = new Spawner(ip, 10);
    sf::Vector2f charPos;
    for(int i=0 ; i<_levelImage.getSize().x ; i++) {
        for(int j=0 ; j<_levelImage.getSize().y ; j++) {
            sf::Vector2i pos(i, j);
            sf::Color c = _levelImage.getPixel(i, j);
            if(c == sf::Color(0, 0, 0, 0)) {
                _map->SetTile(pos, 0);
            } else if(c == sf::Color(122, 137, 60)) {
                _map->SetTile(pos, 1);
            } else if(c == sf::Color(80, 80, 80)) {
                _map->SetTile(pos, rand()%2+2);
            } else if(c == sf::Color(255, 255, 255)) {
                charPos = sf::Vector2f(pos)*16.f;
            } else {
                _map->SetTile(pos, 0);
            }

            if(c.r == 127 && c.g == 127 && c.b == 127 && c.a != 0) {
                Pipe *p = new Pipe(ip, sf::Vector2f(pos)*16.f, c.a*2.f);
                _spawner->AddPipe(p);
            }
        }
    }

    if(!_spawner->SpawnCharacter(character)) {
        character.setPosition(charPos);
    }

    _background = new Background(ip, _levelInfos[name]._backgroundName, _levelInfos[name]._backgroundZoom);
    _grass = new Grass(ip, *this);
}

void Level::NextLevel(IP& ip, EntityManager& eManager, Character& character) {
    /*if(_curLevel == "rockyCave") {
        Load(ip, "rockyCave2", character);
    } else {
        Load(ip, "rockyCave", character);
    }*/
    Load(ip, "rockyCave", character);
    eManager.Clear();
}
