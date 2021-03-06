#include "Level.h"
#include "IP.h"
#include "Map.h"
#include "ResourceLoader.h"
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
#include "Particle.h"
#include "Duck.h"
#include "Mouse.h"
#include "Skull.h"
#include "MathHelper.h"
#include "GUI.h"
#include "Stalactite.h"
#include "Snowflakes.h"
#include "Player.h"
#include "WaterGrass.h"
#include "Bubble.h"

Level::Level(IP& ip, Player& player, ParticleManager& pManager) {
    Character& character(player.GetCharacter());
    _levelInfos["intro"] = LevelInfo{"level0", "nightBackground", 0.0001f, true, false, false};
    _levelInfos["rockyCave"] = LevelInfo{"level1", "rockyBackground", 0.2f, true, true, false};
    _levelInfos["miniBoss1"] = LevelInfo{"miniBoss1", "rockyBackground", 0.2f, false, false, false};
    _levelInfos["miniBoss2"] = LevelInfo{"miniBoss2", "rockyBackground", 0.2f, false, false, false};
    _levelInfos["miniBoss3"] = LevelInfo{"miniBoss3", "lavaBackground", 0.3f, true, false, false};
    _levelInfos["wetCave"] = LevelInfo{"level2", "rockyBackground", 0.2f, true, true, false};
    _levelInfos["waterCave"] = LevelInfo{"waterLevel", "waterBackground", 0.3f, false, false, false};
    _levelInfos["lavaCave"] = LevelInfo{"level3", "lavaBackground", 0.3f, true, false, true};
    _levelInfos["iceCave"] = LevelInfo{"level4", "iceBackground", 0.3f, false, false, false};
    _map = 0;
    _spawner = 0;
    _grass = 0;
    _waterGrass = 0;
    _background = 0;
    _difficulty = 20;
    Load(ip, "wetCave", player, pManager);
    //character.setPosition(character.getPosition() + sf::Vector2f(0, 50));
    character.LeavePipe();
    _lavaTexture.create(/*_map->GetSize().x*/64*16, /*_map->GetSize().y*/38*16);
    _lavaShader.loadFromFile("shaders/lava.frag", sf::Shader::Fragment);
    _flakes = new SnowFlakes(ip);
}

Level::~Level() {
    delete _map;
    _map = 0;
    delete _spawner;
    _spawner = 0;
    delete _grass;
    _grass = 0;
    delete _waterGrass;
    _waterGrass = 0;
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
    for(int i=0 ; i<_passiveEntities.size() ; i++) {
        delete _passiveEntities[i];
        _passiveEntities[i] = 0;
    }
    _passiveEntities.clear();
    for(int i=0 ; i<_stalactites.size() ; i++) {
        delete _stalactites[i];
        _stalactites[i] = 0;
    }
    _stalactites.clear();
    for(int i=0 ; i<_bubbles.size() ; i++) {
        delete _bubbles[i];
        _bubbles[i] = 0;
    }
    _bubbles.clear();
    delete _flakes;
    _flakes = 0;
}

void Level::Update(IP& ip, EntityManager& eManager, Player& player, float eTime, ParticleManager& pManager, BulletManager& bManager, GUI& gui, sf::View& prevView) {
    Character& character(player.GetCharacter());
    _spawner->Update(ip, eTime, eManager, *this, character, gui);
    _grass->Update(ip);
    _waterGrass->Update(ip);
    _background->Update(ip, eTime);
    for(int i=0 ; i<_chests.size() ; i++) {
        _chests[i]->Update(ip, eTime, *this, pManager);
    }
    for(int i=0 ; i<_waterFields.size() ; i++) {
        _waterFields[i]->Update(ip, eTime, pManager);
    }
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        _waterFalls[i]->Update(ip, eTime, *this, pManager);
    }
    for(int i=0 ; i<_passiveEntities.size() ; i++) {
        _passiveEntities[i]->Update(ip, eTime, *this, eManager, pManager);
    }
    for(int i=0 ; i<_stalactites.size() ; i++) {
        _stalactites[i]->Update(ip, eTime, *this, character, pManager, eManager);
    }
    for(int i=0 ; i<_bubbles.size() ; i++) {
        _bubbles[i]->Update(ip, eTime, *this);
        if(!_bubbles[i]->IsAlive()) {
            delete _bubbles[i];
            _bubbles[i] = 0;
            _bubbles.erase(_bubbles.begin() + i);
            i--;
        }
    }
    if((_curLevel == "miniBoss1" || _curLevel == "miniBoss2" || _curLevel == "miniBoss3") && _spawner->IsFinished()) {
        NextLevel(ip, eManager, bManager, player, pManager);
        character.LeavePipe();
    }

    //snow!
    if(_curLevel == "iceCave") {
        _flakes->Update(ip, eTime, *this, pManager, prevView);
    }

    //bubbles!
    if(_curLevel == "waterLevel") {
        float bTime(64000.f / _map->GetSize().x);
        if(_bubbleTimer.getElapsedTime().asMilliseconds() >= bTime) {
            _bubbleTimer.restart();
            _bubbles.push_back(new Bubble(ip, *_map));
        }
    }
}

void Level::DrawBack(IP& ip, sf::View& prevView) {
    _background->Draw(ip._renderer->GetTexture(), prevView);
    //snow!
    if(_curLevel == "iceCave") {
        _flakes->Draw(ip, prevView);
    }
    _map->DrawLayer(ip._renderer->GetTexture(), Map::BACK);
    for(int i=0 ; i<_waterFalls.size() ; i++) {
        _waterFalls[i]->Draw(ip);
    }
    for(int i=0 ; i<_chests.size() ; i++) {
        _chests[i]->Draw(ip);
    }
    for(int i=0 ; i<_passiveEntities.size() ; i++) {
        _passiveEntities[i]->Draw(ip);
    }
    for(int i=0 ; i<_backSprites.size() ; i++) {
        ip._renderer->Draw(_backSprites[i]);
    }
    for(int i=0 ; i<_bubbles.size() ; i++) {
        _bubbles[i]->Draw(ip);
    }
    for(int i=0 ; i<_stalactites.size() ; i++) {
        _stalactites[i]->Draw(ip);
    }
}

void Level::DrawFront(IP& ip, sf::View& prevView) {
    _lavaTexture.clear(sf::Color(0, 0, 0, 0));
    for(int i=0 ; i<_waterFields.size() ; i++) {
        _waterFields[i]->Draw(ip, _lavaTexture);
    }
    _lavaTexture.display();
    sf::Sprite spt;
    spt.setTexture(_lavaTexture.getTexture());
    _lavaShader.setParameter("texture", _lavaTexture.getTexture());
    _lavaShader.setParameter("time", _timer.getElapsedTime().asSeconds());
    ip._renderer->Draw(spt, &_lavaShader);

    _spawner->Draw(ip);
    _waterGrass->Draw(ip._renderer->GetTexture());
    _map->DrawLayer(ip._renderer->GetTexture(), Map::FRONT);
    _grass->Draw(ip._renderer->GetTexture());
}

Map& Level::GetMap() const {
    return *_map;
}

Spawner& Level::GetSpawner() {
    return *_spawner;
}

void Level::Load(IP& ip, std::string name, Player& player, ParticleManager& pManager) {
    Character& character(player.GetCharacter());
    _curLevel = name;
    LevelInfo& info(_levelInfos[name]);
    _levelImages = std::vector<sf::Image>(2);
    _levelImages[0] = sf::Image(ResourceLoader::GetImage(info._imageName + "back"));
    _levelImages[1] = sf::Image(ResourceLoader::GetImage(info._imageName + "front"));
    delete _map;
    _map = new Map(ip, sf::Vector2i(_levelImages[0].getSize()));
    pManager.Clear();
    delete _spawner;
    if(name == "miniBoss1" || name == "miniBoss2" || name == "miniBoss3") {
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
    for(int i=0 ; i<_passiveEntities.size() ; i++) {
        delete _passiveEntities[i];
        _passiveEntities[i] = 0;
    }
    _passiveEntities.clear();
    for(int i=0 ; i<_stalactites.size() ; i++) {
        delete _stalactites[i];
        _stalactites[i] = 0;
    }
    _stalactites.clear();
    for(int i=0 ; i<_bubbles.size() ; i++) {
        delete _bubbles[i];
        _bubbles[i] = 0;
    }
    _bubbles.clear();
    _backSprites.clear();

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
                } else if(c == sf::Color(150, 22, 22)) {
                    _map->SetTile(pos, 9, l);
                } else if(c == sf::Color(25, 139, 168)) {
                    _map->SetTile(pos, 10, l);
                } else if(c == sf::Color(48, 75, 96)) {
                    _map->SetTile(pos, 11, l);
                } else if(c == sf::Color(142, 125, 95)) {
                    _map->SetTile(pos, 12, l);
                } else if(c == sf::Color(91, 80, 61)) {
                    _map->SetTile(pos, 13, l);
                } else if(c == sf::Color(81, 73, 61)) {
                    _map->SetTile(pos, 14, l);
                } else if(c == sf::Color(53, 14, 45)) {
                    _map->SetTile(pos, 15, l);
                } else if(c == sf::Color(145, 165, 173)) {
                    //igloo
                    sf::Sprite s(ResourceLoader::GetTexture("igloo"));
                    s.setOrigin(sf::Vector2f(sf::Vector2i(sf::Vector2f(s.getTextureRect().width/2.f, s.getTextureRect().height))));
                    s.setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(pos*16) + sf::Vector2f(8, 17))));
                    _backSprites.push_back(s);
                } else if(c == sf::Color(204, 220, 224)) {
                    Stalactite *s = new Stalactite(pos);
                    _stalactites.push_back(s);
                } else if(c == sf::Color(99, 40, 40)) {
                    //water plant
                    sf::Sprite s(ResourceLoader::GetTexture("waterPlants"));
                    s.setTextureRect(sf::IntRect(rand()%3*16, 0, 16, 16));
                    s.setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(pos*16) + sf::Vector2f(0, 2))));
                    _backSprites.push_back(s);
                } else if(c == sf::Color(106, 129, 193)) {
                    _map->SetTile(pos, 0, l);
                } else if(c == sf::Color(255, 255, 255)) {
                    charPos = sf::Vector2f(pos)*16.f;
                } else {
                    _map->SetTile(pos, 0, l);
                }

                if((c.r == 127 && c.g == 127 && c.b == 127 && c.a != 0) || (c.r == 127 && c.g == 127 && c.b == 255 && c.a != 0)) {
                    Pipe *p = new Pipe(ip, sf::Vector2f(pos)*16.f, c.a*2.f);
                    _spawner->AddPipe(p);
                }
            }
        }
    }

    //second pass to load fluids and ducks
    int w = _levelImages[0].getSize().x;
    int h = _levelImages[0].getSize().y;
    sf::Color waterSufaceC(106, 129, 193);
    sf::Color waterC(70, 94, 160);
    sf::Color waterC2(127, 127, 255); //if pipe
    sf::Color waterFallC(70, 94, 160, 130);
    sf::Color bigWaterFallC(70, 94, 160, 180);
    sf::Color lavaSufaceC(255, 159, 43);
    sf::Color lavaC(216, 135, 36);
    sf::Color lavaFallC(216, 135, 36, 130);
    sf::Color bigLavaFallC(216, 135, 36, 180);
    for(int i=0 ; i<w ; i++) {
        for(int j=0 ; j<h ; j++) {
            //fluids
            if(_levelImages[1].getPixel(i, j) == waterSufaceC || _levelImages[1].getPixel(i, j) == lavaSufaceC) {
                bool isLava = _levelImages[1].getPixel(i, j)==lavaSufaceC;
                bool isLimited = true;
                sf::Vector2i s(GetRectSizeInImageAt(_levelImages[1], sf::Vector2i(i, j), _levelImages[1].getPixel(i, j)));
                float offsets[2]{0};
                if(_map->GetTileType(sf::Vector2i(i-1, j), Map::FRONT) != Map::VOID) {
                    offsets[0] = 2;
                }
                if(_map->GetTileType(sf::Vector2i(i+s.x, j), Map::FRONT) != Map::VOID) {
                    offsets[1] = 2;
                }
                sf::FloatRect fluidRect(i*16-offsets[0], j*16+8, s.x*16+offsets[0]+offsets[1], s.y*16-8);
                if(isLava && name == "miniBoss3") {
                    isLimited = false;
                    fluidRect.height = 12*16;
                }
                _waterFields.push_back(new WaterField(fluidRect, isLava?4:2, true, isLava, isLimited, false));
                if(_levelInfos[name]._addDucks) {
                    sf::FloatRect rect(_waterFields[GetNbWaterFields()-1]->GetRect());
                    int nbDucks = (int)(MathHelper::RandFloat(0, 1)*MathHelper::RandFloat(0, 1)*((float)s.x/3.f));
                    for(int k=0 ; k<nbDucks ; k++) {
                        Duck *duck = new Duck(ip);
                        duck->setPosition(sf::Vector2f(MathHelper::RandFloat(rect.left+duck->getGlobalBounds().width/2.f, rect.left+rect.width-duck->getGlobalBounds().width/2.f), rect.top));
                        _passiveEntities.push_back(duck);
                    }
                }
            } else if(_levelImages[1].getPixel(i, j) == waterC || _levelImages[1].getPixel(i, j) == lavaC || (_levelImages[1].getPixel(i, j).r == waterC2.r && _levelImages[1].getPixel(i, j).g == waterC2.g && _levelImages[1].getPixel(i, j).b == waterC2.b)) {
                //sf::Vector2i s(1, 1);
                float offsets[4]{0};
                sf::Vector2i testPos[4] = {sf::Vector2i(i-1, j), sf::Vector2i(i+1, j), sf::Vector2i(i, j-1), sf::Vector2i(i, j+1)};
                for(int i=0 ; i<4 ; i++) {
                    if(_map->GetTileType(testPos[i], Map::FRONT) != Map::VOID) {
                        offsets[i] = 2;
                    }
                }
                _waterFields.push_back(new WaterField(sf::FloatRect(i*16-offsets[0], j*16-offsets[2], 16+offsets[0]+offsets[1], 16+offsets[2]+offsets[3]), 2, false, _levelImages[1].getPixel(i, j)==lavaC, true, _curLevel=="waterCave"));
            }
            //falls
            if(_levelImages[0].getPixel(i, j) == waterFallC) {
                _waterFalls.push_back(new WaterFall(ip, sf::Vector2i(i, j), false, false));
            } else if(_levelImages[0].getPixel(i, j) == bigWaterFallC) {
                _waterFalls.push_back(new WaterFall(ip, sf::Vector2i(i, j), true, false));
            } else if(_levelImages[0].getPixel(i, j) == lavaFallC) {
                _waterFalls.push_back(new WaterFall(ip, sf::Vector2i(i, j), false, true));
            } else if(_levelImages[0].getPixel(i, j) == bigLavaFallC) {
                _waterFalls.push_back(new WaterFall(ip, sf::Vector2i(i, j), true, true));
            }
        }
    }
    //make the waterfalls, huh, fall.
    for(int i=_waterFalls.size()-1 ; i>=0 ; i--) {
        _waterFalls[i]->Fall(ip, *this);
    }

    //add some passive things
    //mice
    if(_levelInfos[name]._addMice) {
        for(int i=0 ; i<_map->GetSize().x ; i++) {
            for(int j=0 ; j<_map->GetSize().y ; j++) {
                sf::Vector2i pos(i, j);
                if(_map->GetTileType(pos, Map::FRONT)==Map::VOID && _map->GetTileType(pos+sf::Vector2i(0, 1), Map::FRONT)==Map::WALL && rand()%20==0) {
                    Mouse *mouse = new Mouse(ip);
                    mouse->setPosition(sf::Vector2f(pos)*16.f + sf::Vector2f(8, 12));
                    if(mouse->IsInWater(*this)) {
                        continue;
                    }
                    _passiveEntities.push_back(mouse);
                }
            }
        }
    }

    //skull
    if(_levelInfos[name]._addSkulls) {
        sf::Vector2i pos(42, 42);
        bool correctPos = false;
        Skull *skull(0);
        while(!correctPos) {
            correctPos = false;
            pos = sf::Vector2i(MathHelper::RandInt(0, _map->GetSize().x), MathHelper::RandInt(0, _map->GetSize().y));
            if(_map->GetTileType(pos, Map::FRONT)==Map::VOID && _map->GetTileType(pos+sf::Vector2i(0, 1), Map::FRONT)==Map::WALL) {
                correctPos = true;
            }
            skull = new Skull(ip);
            skull->setPosition(sf::Vector2f(pos)*16.f + sf::Vector2f(8, 8));
            if(skull->IsInWater(*this) || _spawner->IsCollided(*skull)) {
                skull = 0;
                correctPos = false;
            }
        }
        if(skull != 0) {
            _passiveEntities.push_back(skull);
        }
    }

    if(!_spawner->SpawnCharacter(character)) {
        character.setPosition(charPos);
    }

    delete _background;
    _background = new Background(ip, _levelInfos[name]._backgroundName, _levelInfos[name]._backgroundZoom, *_map);
    delete _grass;
    _grass = new Grass(ip, *_map);
    delete _waterGrass;
    _waterGrass = new WaterGrass(ip, *_map);
    for(int i=0 ; i<_chests.size() ; i++) {
        delete _chests[i];
        _chests[i] = 0;
    }
    /*_chests.clear();
    _chests.push_back(new Chest(ip, sf::Vector2f(_map->GetSize().x*8, 30)));*/
}


sf::Vector2i Level::GetRectSizeInImageAt(sf::Image& img, sf::Vector2i pos, sf::Color c) {
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

void Level::NextLevel(IP& ip, EntityManager& eManager, BulletManager& bManager, Player& player, ParticleManager& pManager) {
    Character& character(player.GetCharacter());
    /*if(_curLevel == "rockyCave") {
        Load(ip, "rockyCave2", character);
    } else {
        Load(ip, "rockyCave", character);
    }*/
    //Load(ip, /*"rockyCave"*/"miniBoss1", character);
    std::string toLoad;
    if(_curLevel == "intro") {
        toLoad = "rockyCave";
    } else if(_curLevel == "rockyCave") {
        toLoad = "miniBoss1";
    } else if(_curLevel == "miniBoss1") {
        toLoad = "wetCave";
    } else if(_curLevel == "wetCave") {
        toLoad = "miniBoss2";
    } else if(_curLevel == "miniBoss2") {
        toLoad = "waterCave";
    } else if(_curLevel == "waterCave") {
        toLoad = "lavaCave";
    } else if(_curLevel == "lavaCave") {
        toLoad = "miniBoss3";
    } else if(_curLevel == "miniBoss3") {
        toLoad = "iceCave";
    } else {
        toLoad = "iceCave";
    }
    Load(ip, toLoad, player, pManager);
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

bool Level::IsInWater(sf::Sprite spt, bool lava) {
    for(int i=0 ; i<GetNbWaterFields() ; i++) {
        WaterField& wf(*_waterFields[i]);
        if(wf.IsLava() != lava) {
            continue;
        }
        if(spt.getGlobalBounds().intersects(wf.GetRect())) {
            return true;
        }
    }
    return false;
}

void Level::AddWaterFall(IP& ip, sf::Vector2i tilePos, bool big, bool lava) {
    _waterFalls.push_back(new WaterFall(ip, tilePos, big, lava));
}

int Level::GetNbPassiveEntities() {
    return _passiveEntities.size();
}

GameEntity* Level::GetPassiveEntity(int id) {
    if(id < 0 || id >=GetNbPassiveEntities()) {
        return 0;
    }
    return _passiveEntities[id];
}

std::string Level::GetName() {
    return _curLevel;
}

void Level::AddBubble(Bubble* b) {
    _bubbles.push_back(b);
}
