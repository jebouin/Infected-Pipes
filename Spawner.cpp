#include "Spawner.h"
#include "IP.h"
#include "EntityManager.h"
#include "MovingSprite.h"
#include "Pipe.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "Character.h"

Spawner::Spawner(IP& ip, int nbWaves) {
    _curWave = 0;
    _difficulty = 2;
    _nbWaves = nbWaves;
    _spawning = true;
    _nbToSpawn = 16;
    _finished = false;

    NextWave();
}

Spawner::~Spawner() {
    for(int i=0 ; i<_pipes.size() ; i++) {
        delete _pipes[0];
        _pipes.erase(_pipes.begin());
    }
}

void Spawner::Update(IP& ip, EntityManager& eManager) {
    if(_spawning) {
        if(_clock.getElapsedTime().asMilliseconds() > 100) {
            for(int i=0 ; i<_pipes.size() ; i++) {
                _pipes[i]->Spawn(ip, eManager);
                _nbToSpawn--;

                if(_nbToSpawn == 0) {
                    _spawning = false;
                    break;
                }
            }
            _clock.restart();
        }
    }

    if(eManager.GetNbEnnemies() == 0 && !_finished && !_spawning) {
        NextWave();
    }

    for(int i=0 ; i<_pipes.size() ; i++) {
        _pipes[i]->Update(ip, eManager);
    }
}

void Spawner::NextWave() {
    _curWave++;
    if(_curWave > _nbWaves) {
        _finished = true;
        _spawning = false;
        cout << "Finished!" << endl;
        return;
    }
    _nbToSpawn = /*_difficulty*/pow(2, _curWave);
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
            if(dist < 5) {
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
