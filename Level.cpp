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
#include "WaterFall.h"
#include "ParticleManager.h"

Level::Level(IP& ip, Character& character) {
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground", 0.0001f};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "rockyBackground", 0.2f};
    _levelInfos["miniBoss1"] = LevelInfo{"miniBoss1", "rockyBackground", 0.2f};
    _levelInfos["wetCave"] = LevelInfo{"level2", "rockyBackground", 0.2f};
    _map = 0;
    _spawner = 0;
    _grass = 0;
    _background = 0;
    _difficulty = 2;
    Load(ip, "wetCave", character);
    character.setPosition(character.getPosition() + sf::Vector2f(0, 50));
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
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        delete _waterFalls[i];
        _waterFalls[i] = 0;
    }
    _waterFalls.clear();
}

void Level::Update(IP& ip, EntityManager& eManager, Character& character, float eTime, ParticleManager& pManager) {
    _spawner->Update(ip, eManager, *this, character);
    _grass->Update(ip);
    _background->Update(ip, eTime);
    for(int i=0 ; i<_chests.size() ; i++) {
        _chests[i]->Update(ip, eTime, *this, pManager);
    }
    for(int i=0 ; i<_waterFields.size() ; i++) {
        _waterFields[i]->Update(eTime);
    }
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        _waterFalls[i]->Update(ip, eTime, *this);
    }
}

void Level::DrawBack(IP& ip, sf::View& prevView) {
    _background->Draw(ip, prevView);
    _map->DrawLayer(ip, Map::BACK);
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        _waterFalls[i]->Draw(ip);
    }
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
    if(name == "miniBoss1") {
        _spawner = new Spawner(ip, 1, *this);
    } else {
        _spawner = new Spawner(ip, 20, *this);
    }


    for(int i=0 ; i<_waterFields.size() ; i++) {
        delete _waterFields[i];
        _waterFields[i] = 0;
    }
    _waterFields.clear();
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        delete _waterFalls[i];
        _waterFalls[i] = 0;
    }
    _waterFalls.clear();
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
                } else if(c == sf::Color(51, 51, 51)) {
                    _map->SetTile(pos, 6, l);
                } else if(c == sf::Color(56, 45, 26, 128)) {
                    _map->SetTile(pos, 7, l);
                } else if(c == sf::Color(51, 51, 51, 200)) {
                    _map->SetTile(pos, 8, l);
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
    sf::Color waterSufaceC(106, 129, 193);
    sf::Color waterC(70, 94, 160);
    sf::Color waterFallC(70, 94, 160, 130);
    for(int i=0 ; i<w ; i++) {
        for(int j=0 ; j<h ; j++) {
            if(_levelImages[1].getPixel(i, j) == waterSufaceC) {
                sf::Vector2i s(GetRectSizeInImageAt(_levelImages[1], sf::Vector2i(i, j), waterSufaceC));
                float offsets[2]{0};
                if(_map->GetTileType(sf::Vector2i(i-1, j), Map::FRONT) != Map::VOID) {
                    offsets[0] = 2;
                }
                if(_map->GetTileType(sf::Vector2i(i+s.x, j), Map::FRONT) != Map::VOID) {
                    offsets[1] = 2;
                }
                _waterFields.push_back(new WaterField(sf::FloatRect(i*16-offsets[0], j*16+8, s.x*16+offsets[0]+offsets[1], s.y*16-8), 4, true));
            } else if(_levelImages[1].getPixel(i, j) == waterC) {
                sf::Vector2i s(1, 1);
                float offsets[4]{0};
                sf::Vector2i testPos[4] = {sf::Vector2i(i-1, j), sf::Vector2i(i+s.x, j), sf::Vector2i(i, j-1), sf::Vector2i(i, j+1)};
                for(int i=0 ; i<4 ; i++) {
                    if(_map->GetTileType(testPos[i], Map::FRONT) != Map::VOID) {
                        offsets[i] = 2;
                    }
                }
                _waterFields.push_back(new WaterField(sf::FloatRect(i*16-offsets[0], j*16-offsets[2], s.x*16+offsets[0]+offsets[1], s.y*16+offsets[2]+offsets[3]), 2, false));
            } else if(_levelImages[0].getPixel(i, j) == waterFallC) {
                _waterFalls.push_back(new WaterFall(ip, sf::Vector2i(i, j)));
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
    /*_chests.clear();
    _chests.push_back(new Chest(ip, sf::Vector2f(_map->GetSize().x*8, 30)));*/
}


sf::Vector2i Level::GetRectSizeInImageAt(sf::Image& img, sf::Vector2i pos, sf::Color& c) {
    /*int w = 100000;
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

    return sf::Vector2i(w, h);*/
    int w = 100000;

    for(int i=0 ; i<w ; i++) {
        if(img.getPixel(i+pos.x, pos.y) != c) {
            if(i == 0) {
                break;
            } else {
                w = i;
            }
            break;
        } else {
            img.setPixel(i+pos.x, pos.y, sf::Color(255, 255, 255, 0));
        }
    }

    return sf::Vector2i(w, 1);
}

void Level::NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Character& character) {
    /*if(_curLevel == "rockyCave") {
        Load(ip, "rockyCave2", character);
    } else {
        Load(ip, "rockyCave", character);
    }*/
    Load(ip, /*"rockyCave"*/"miniBoss1", character);
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

string Level::GetName() {
    return _curLevel;
}
