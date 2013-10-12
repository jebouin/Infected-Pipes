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
#include "Chest.h"
#include "WaterField.h"
#include "ParticleManager.h"

Level::Level(IP& ip, Character& character) {
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground", 0.0001f};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "rockyBackground", 0.2f};
    _levelInfos["rockyCave2"] = LevelInfo{"level2", "rockyBackground", 0.2f};
    _map = 0;
    _spawner = 0;
    _grass = 0;
    _background = 0;
    _difficulty = 2;
    Load(ip, "intro", character);
}

Level::~Level() {
    delete _map;
    _map = 0;
    delete _spawner;
    _spawner = 0;
    delete _grass;
    _grass = 0;
    delete _background;
    _background = 0;
    for(int i=0 ; i<_chests.size() ; i++) {
        delete _chests[i];
        _chests[i] = 0;
    }
    _chests.clear();
    for(int i=0 ; i<_waterFields.size() ; i++) {
        delete _waterFields[i];
        _waterFields[i] = 0;
    }
    _waterFields.clear();
}

void Level::Update(IP& ip, EntityManager& eManager, Character& character, float eTime, ParticleManager& pManager) {
    _spawner->Update(ip, eManager, *this, character);
    _grass->Update(ip);
    for(int i=0 ; i<_chests.size() ; i++) {
        _chests[i]->Update(ip, eTime, *this, pManager);
    }
    for(int i=0 ; i<_waterFields.size() ; i++) {
        _waterFields[i]->Update(eTime);
    }
}

void Level::DrawBack(IP& ip, sf::View& prevView) {
    _background->Draw(ip, prevView);
    _map->DrawLayer(ip, Map::BACK);
    for(int i=0 ; i<_chests.size() ; i++) {
        _chests[i]->Draw(ip);
    }
}

void Level::DrawFront(IP& ip) {
    for(int i=0 ; i<_waterFields.size() ; i++) {
        _waterFields[i]->Draw(ip);
    }
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
    delete _map;
    _map = new Map(ip, sf::Vector2i(_levelImages[0].getSize()));
    delete _spawner;
    _spawner = new Spawner(ip, 10, *this);
    for(int i=0 ; i<_waterFields.size() ; i++) {
        delete _waterFields[i];
        _waterFields[i] = 0;
    }
    _waterFields.clear();
    sf::Vector2f charPos;

    //first pass to load single tiles
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
                } else if(c == sf::Color(106, 129, 193)) {
                    _map->SetTile(pos, 0, l);
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

    //second pass to load fluids
    int w = _levelImages[0].getSize().x;
    int h = _levelImages[0].getSize().y;
    sf::Color wc(106, 129, 193);
    for(int i=0 ; i<w ; i++) {
        for(int j=0 ; j<h ; j++) {
            if(_levelImages[1].getPixel(i, j) == wc) {
                sf::Vector2i s(GetRectSizeInImageAt(_levelImages[1], sf::Vector2i(i, j), wc));
                _waterFields.push_back(new WaterField(sf::FloatRect(i*16-1, j*16+12, s.x*16+2, s.y*16-12+2), 2));
            }
        }
    }

    if(!_spawner->SpawnCharacter(character)) {
        character.setPosition(charPos);
    }


    delete _background;
    _background = new Background(ip, _levelInfos[name]._backgroundName, _levelInfos[name]._backgroundZoom, *this);
    delete _grass;
    _grass = new Grass(ip, *this);
    for(int i=0 ; i<_chests.size() ; i++) {
        delete _chests[i];
        _chests[i] = 0;
    }
    _chests.clear();
    //_chests.push_back(new Chest(ip, sf::Vector2f(_map->GetSize().x*8, 30)));
}


sf::Vector2i Level::GetRectSizeInImageAt(sf::Image& img, sf::Vector2i pos, sf::Color& c) {
    int w = 100000;
    int h = 0;

    while(42) {
        bool end = false;
        for(int i=0 ; i<w ; i++) {
            if(img.getPixel(i+pos.x, h+pos.y) != c) {
                if(i == 0) {
                    end = true;
                } else {
                    w = i;
                }
                break;
            } else {
                img.setPixel(i+pos.x, h+pos.y, sf::Color(255, 255, 255, 0));
            }
        }
        if(end) {
            break;
        }
        h++;
    }

    return sf::Vector2i(w, h);
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

void Level::OpenChest(Character& character, IP& ip) {
    for(int i=0 ; i<_chests.size() ; i++) {
        if(_chests[i]->GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
            _chests[i]->Open(ip);
        }
    }
}

int Level::GetNbWaterFields() {
    return _waterFields.size();
}

WaterField& Level::GetWaterField(int id) {
    return *_waterFields[id];
}
