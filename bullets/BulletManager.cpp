#include "BulletManager.h"
#include "Bullet.h"
#include "Level.h"
#include "Character.h"
#include "ParticleManager.h"
#include "EntityManager.h"

BulletManager::BulletManager() {

}

BulletManager::~BulletManager() {
    Clear();
}

void BulletManager::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    for(int i=0 ; i<_bullets.size() ; i++) {
        _bullets[i]->Update(ip, eTime, level, character, pManager, eManager);
        if(!_bullets[i]->IsAlive()) {
            delete _bullets[i];
            _bullets[i] = 0;
            _bullets.erase(_bullets.begin() + i);
            i--;
        }
    }
}

void BulletManager::Draw(IP& ip) {
    for(int i=0 ; i<_bullets.size() ; i++) {
        _bullets[i]->Draw(ip);
    }
}

void BulletManager::AddBullet(Bullet* bullet) {
    _bullets.push_back(bullet);
}

void BulletManager::Clear() {
    for(int i=0 ; i<_bullets.size() ; i++) {
        delete _bullets[i];
        _bullets[i] = 0;
    }
    _bullets.clear();
}

int BulletManager::GetCount() {
    return _bullets.size();
}

Bullet* BulletManager::GetBullet(int id) {
    if(id < 0 || id >= _bullets.size()) {
        return 0;
    }
    return _bullets[id];
}
