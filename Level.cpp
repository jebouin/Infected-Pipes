#include "Level.h"
#include "IP.h"
#include "Map.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "Pipe.h"
#include "Spawner.h"
#include "EntityManager.h"
#include "BulletManager.h"
#include "Background.h"
#include "Grass.h"
#include "Character.h"

Level::Level(IP& ip, Character& character) {
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground", 0.0001f};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "rockyBackground", 0.2f};
    _levelInfos["rockyCave2"] = LevelInfo{"level2", "rockyBackground", 0.2f};
    Load(ip, "intro", character);
    _difficulty = 0;
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
    _map->DrawLayer(ip, Map::BACK);
}

void Level::DrawFront(IP& ip) {
    _spawner->Draw(ip);
    _map->DrawLayer(ip, Map::FRONT);
    _grass->Draw(ip);
}

Map& Level::GetMap() const {
    return *_map;
}

Spawner& Level::GetSpawner() {
    return *_spawner;
}

void Level::Load(IP& ip, string name, Character& character) {
    _curLevel = name;
    LevelInfo& info(_levelInfos[name]);
    _levelImages = vector<sf::Image>(2);
    _levelImages[0] = sf::Image(ip._textureLoader->GetImage(info._imageName + "back"));
    _levelImages[1] = sf::Image(ip._textureLoader->GetImage(info._imageName + "front"));
    _map = new Map(ip, sf::Vector2i(_levelImages[0].getSize()));
    _spawner = new Spawner(ip, 10);
    sf::Vector2f charPos;

    for(int t=0 ; t<2 ; t++) {
        Map::Layer l(static_cast<Map::Layer>(t));
        for(int i=0 ; i<_levelImages[0].getSize().x ; i++) {
            for(int j=0 ; j<_levelImages[0].getSize().y ; j++) {
                sf::Vector2i pos(i, j);
                sf::Color c = _levelImages[t].getPixel(i, j);
                if(c == sf::Color(0, 0, 0, 0)) {
                    _map->SetTile(pos, 0, l);
                } else if(c == sf::Color(122, 137, 60)) {
                    _map->SetTile(pos, 1, l);
                } else if(c == sf::Color(80, 80, 80)) {
                    _map->SetTile(pos, rand()%2+2, l);
                } else if(c == sf::Color(96, 78, 45)) {
                    _map->SetTile(pos, 4, l);
                } else if(c == sf::Color(56, 45, 26)) {
                    _map->SetTile(pos, 5, l);
                } else if(c == sf::Color(255, 255, 255)) {
                    charPos = sf::Vector2f(pos)*16.f;
                } else {
                    _map->SetTile(pos, 0, l);
                }

                if(c.r == 127 && c.g == 127 && c.b == 127 && c.a != 0) {
                    Pipe *p = new Pipe(ip, sf::Vector2f(pos)*16.f, c.a*2.f);
                    _spawner->AddPipe(p);
                }
            }
        }
    }

    if(!_spawner->SpawnCharacter(character)) {
        character.setPosition(charPos);
    }

    _background = new Background(ip, _levelInfos[name]._backgroundName, _levelInfos[name]._backgroundZoom, *this);
    _grass = new Grass(ip, *this);
}

void Level::NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Character& character) {
    /*if(_curLevel == "rockyCave") {
        Load(ip, "rockyCave2", character);
    } else {
        Load(ip, "rockyCave", character);
    }*/
    Load(ip, "rockyCave", character);
    eManager.Clear();
    bManager.Clear();
}

int Level::GetDifficulty() const {
    return _difficulty;
}

void Level::SetDifficulty(int v) {
    _difficulty = v;
}
