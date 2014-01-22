#include "Spawner.h"
#include "IP.h"
#include "EntityManager.h"
#include "MovingSprite.h"
#include "Pipe.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "Character.h"
#include "RockWorm.h"
#include "Spiderock.h"
#include "SnowBallEnemy.h"
#include "Bat.h"
#include "Snail.h"
#include "Slimey.h"
#include "Level.h"
#include "Ennemy.h"
#include "Slime.h"
#include "WormBoss.h"
#include "FireBall.h"
#include "Turtle.h"
#include "GUI.h"
#include "WaveIndicator.h"
#include "SnowMan.h"
#include "FireWormBoss.h"
#include "Fist.h"
#include "FlyingSkull.h"
#include "MissileBall.h"

Spawner::Spawner(IP& ip, int nbWaves, Level& l) {
    _curWave = 0;
    _nbWaves = nbWaves;
    _spawning = true;
    _finished = false;
}

Spawner::~Spawner() {
    for(int i=0 ; i<_pipes.size() ; i++) {
        delete _pipes[i];
        _pipes[i] = 0;
    }
    _pipes.clear();
}

void Spawner::Update(IP& ip, float eTime, EntityManager& eManager, Level& level, Character& character, GUI& gui) {
    if(_curWave==0 || (_curWave < _nbWaves && _nextWaveTimer.getElapsedTime().asSeconds() >= 20.f)) {
        NextWave(ip, level, gui);
    }

    if(_spawning) {
        if(_clock.getElapsedTime().asMilliseconds() > 100) {
            Spawn(ip, eManager, level, character);
            _clock.restart();
        }
    }

    if(eManager.GetNbEnnemies() == 0 && !_finished && !_spawning) {
        NextWave(ip, level, gui);
    }

    /*if(level.GetName() == "miniBoss1") {
        if(rand()%100==0) {
            Slime *slime = new Slime(ip, level);
            slime->setPosition(sf::Vector2f(26*16, -15));
            eManager.Add(slime);
        }
    }*/

    for(int i=0 ; i<_pipes.size() ; i++) {
        _pipes[i]->Update(ip, eManager);
    }
}

void Spawner::Spawn(IP& ip, EntityManager& eManager, Level& level, Character& character) {
    std::string levelName = level.GetName();
    if(levelName == "miniBoss1") {
        Slimey *slimey = new Slimey(ip, level);
        eManager.Add(slimey);
        _difToSpawn = 0;
    } else if(levelName == "miniBoss2") {
        for(int i=0 ; i<2 ; i++) {
            WormBoss *wormBoss = new WormBoss(ip, level);
            eManager.Add(wormBoss);
            _difToSpawn = 0;
        }
    } else if(levelName == "miniBoss3") {
        FireWormBoss *fireWormBoss = new FireWormBoss(ip, level);
        eManager.Add(fireWormBoss);
        _difToSpawn = 0;
    } else if(levelName == "rockyCave" || levelName == "wetCave") {
        int pipeId = rand()%_pipes.size();
        int et;
        static int d[4] = {1, 10, 20, 50};
        for(int i=3 ; i>=0 ; i--) {
            if(d[i] <= _difToSpawn) {
                et = i;
                break;
            }
        }
        switch(et) {
            case 0: {
                _pipes[pipeId]->Spawn(ip, eManager, new Spiderock(ip, level));
                break;
             } case 1: {
                RockWorm *r = new RockWorm(ip, level);
                if(!r->AutoSpawn(ip, level, eManager, character)) {
                    delete r;
                    return;
                }
                eManager.Add(r);
                break;
            } case 2: {
                _pipes[pipeId]->Spawn(ip, eManager, new Bat(ip, level));
                break;
            } case 3: {
                _pipes[pipeId]->Spawn(ip, eManager, new Snail(ip, level));
                break;
            }
        }

        _difToSpawn -= d[et];
    } else if(levelName == "lavaCave") {
        int pipeId = rand()%_pipes.size();
        /*int et(0);
        static int d[2] = {200, 500};
        for(int i=1 ; i>=0 ; i--) {
            if(d[i] <= _difToSpawn) {
                et = i;
                break;
            }
        }
        switch(et) {
            case 0: {
                FireBall *f = new FireBall(ip, level);
                if(!f->AutoSpawn(ip, level, eManager, character)) {
                    delete f;
                    f = 0;
                    return;
                }
                eManager.Add(f);
                break;
            } case 1: {
                _pipes[pipeId]->Spawn(ip, eManager, new Turtle(ip, level));
                break;
            }
        }
        _difToSpawn -= d[et];*/
        _difToSpawn -= 32;
        _pipes[pipeId]->Spawn(ip, eManager, new FlyingSkull(ip, level));
    } else if(levelName == "iceCave") {
        /*int pipeId = rand()%_pipes.size();
        int et(0);
        static int d[2] = {200, 500};
        for(int i=1 ; i>=0 ; i--) {
            if(d[i] <= _difToSpawn) {
                et = i;
                break;
            }
        }
        switch(et) {
            case 0: {
                FireBall *f = new FireBall(ip, level);
                if(!f->AutoSpawn(ip, level, eManager, character)) {
                    delete f;
                    f = 0;
                    return;
                }
                eManager.Add(f);
                break;
            } case 1: {
                _pipes[pipeId]->Spawn(ip, eManager, new Turtle(ip, level));
                break;
            }
        }*/
        /*_difToSpawn = 0;
        int pipeId = rand()%_pipes.size();
        _pipes[pipeId]->Spawn(ip, eManager, new SnowMan(ip, level));*/
        /*Fist *f = new Fist(ip, level);
        if(!f->AutoSpawn(ip, level, eManager, character)) {
            delete f;
            return;
        }
        eManager.Add(f);*/
        int pipeId = rand()%_pipes.size();
        _pipes[pipeId]->Spawn(ip, eManager, new MissileBall(ip, level));
        _difToSpawn = 0;
    }

    /*if(rand()%10==0) {
        _pipes[pipeId]->Spawn(ip, eManager, new SnowBallEnemy(ip, level));
    }*/

    if(_difToSpawn <= 0) {
        _spawning = false;
    }
}

void Spawner::NextWave(IP& ip, Level& level, GUI& gui) {
    _nextWaveTimer.restart();
    if(_curWave >= _nbWaves) {
        _finished = true;
        _spawning = false;
        std::cout << "Finished!" << std::endl;
        return;
    }
    _difToSpawn = level.GetDifficulty();
    _curWave++;
    _spawning = true;
    _clock.restart();
    std::cout << "Wave: " << _curWave << std::endl;
    if(level.GetName() == "miniBoss1" || level.GetName() == "miniBoss2" || level.GetName() == "miniBoss3") {
        gui.GetWaveIndicator().AnnounceWave(ip, -42);
    } else {
        gui.GetWaveIndicator().AnnounceWave(ip, _curWave);
    }
}

void Spawner::Draw(IP& ip) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        ip._renderer->Draw(*_pipes[i]);
    }
}

bool Spawner::SpawnCharacter(Character& character) {
    std::vector<int> cp;
    for(int i=0 ; i<_pipes.size() ; i++) {
        if(_pipes[i]->getRotation() == 90) {
            cp.push_back(i);
        }
    }
    if(cp.size()==0) {
        return false;
    }
    int pid=rand()%cp.size();
    character.setPosition(_pipes[cp[pid]]->getPosition());
    return true;
}

void Spawner::AddPipe(Pipe *p) {
    _pipes.push_back(p);
}

bool Spawner::IsFinished() {
    return _finished;
}

bool Spawner::CanEnterPipe(MovingSprite& s) {
    if(!IsOnGround(s) /*|| !IsFinished()*/) {
        return false;
    }
    sf::FloatRect sr(s.GetGlobalHitbox().left, s.GetGlobalHitbox().top+1, s.GetGlobalHitbox().width, s.GetGlobalHitbox().height);
    for(int i=0 ; i<_pipes.size() ; i++) {
        if(sr.intersects(_pipes[i]->getGlobalBounds())) {
            float pipeX = _pipes[i]->getPosition().x;
            float dist = MathHelper::ABS(s.getPosition().x-pipeX);
            if(dist < 6) {
                s.setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(pipeX, s.getPosition().y))));
                return true;
            }
        }
    }
    return false;
}

bool Spawner::IsCollided(sf::FloatRect rect) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        if(rect.intersects(_pipes[i]->getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool Spawner::IsCollided(MovingSprite& sprite, sf::Vector2f pos) {
    return IsCollided(sf::FloatRect(sf::Vector2f(sprite.GetHitbox().left, sprite.GetHitbox().top)+pos, sf::Vector2f(sprite.GetHitbox().width, sprite.GetHitbox().height)));
}

bool Spawner::IsCollided(MovingSprite& sprite) {
    return IsCollided(sprite.GetGlobalHitbox());
}

bool Spawner::IsOnGround(MovingSprite& sprite) {
    sf::FloatRect rect(sprite.GetGlobalHitbox().left, sprite.GetGlobalHitbox().top+sprite.GetGlobalHitbox().height+1, sprite.GetGlobalHitbox().width, 1);
    if(IsCollided(rect)) {
        return true;
    }
    return false;
}
