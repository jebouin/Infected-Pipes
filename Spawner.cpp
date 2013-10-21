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

Spawner::Spawner(IP& ip, int nbWaves, Level& l) {
    _curWave = 0;
    _nbWaves = nbWaves;
    _spawning = true;
    _difToSpawn = _difficulty;
    _finished = false;

    NextWave(l);
}

Spawner::~Spawner() {
    for(int i=0 ; i<_pipes.size() ; i++) {
        delete _pipes[i];
        _pipes[i] = 0;
    }
    _pipes.clear();
}

void Spawner::Update(IP& ip, EntityManager& eManager, Level& level, Character& character) {
    if(_spawning) {
        if(_clock.getElapsedTime().asMilliseconds() > 100) {
            Spawn(ip, eManager, level, character);
            _clock.restart();
        }
    }

    if(eManager.GetNbEnnemies() == 0 && !_finished && !_spawning) {
        NextWave(level);
    }

    /*if(level.GetName() == "miniBoss1") {
        if(rand()%100==0) {
            Slime *slime = new Slime(ip, level);
            slime->setPosition(sf::Vector2f(23*16, -15));
            eManager.Add(slime);
        }
    }*/

    for(int i=0 ; i<_pipes.size() ; i++) {
        _pipes[i]->Update(ip, eManager);
    }
}

void Spawner::Spawn(IP& ip, EntityManager& eManager, Level& level, Character& character) {
    string levelName = level.GetName();

    if(levelName == "miniBoss1") {
        Slimey *slimey = new Slimey(ip, level);
        eManager.Add(slimey);
        _difToSpawn = 0;
    } else {
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
    }




    /*if(rand()%10==0) {
        _pipes[pipeId]->Spawn(ip, eManager, new SnowBallEnemy(ip, level));
    }*/

    if(_difToSpawn <= 0) {
        _spawning = false;
    }
}

void Spawner::NextWave(Level& level) {
    if(_curWave >= _nbWaves) {
        _finished = true;
        _spawning = false;
        cout << "Finished!" << endl;
        return;
    }
    _difToSpawn = level.GetDifficulty();
    _curWave++;
    _spawning = true;
    _clock.restart();
    cout << "Wave: " << _curWave << endl;
}

void Spawner::Draw(IP& ip) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        ip._renderer->Draw(*_pipes[i]);
    }
}

bool Spawner::SpawnCharacter(Character& character) {
    vector<int> cp;
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
                s.setPosition(sf::Vector2f(pipeX, s.getPosition().y));
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
