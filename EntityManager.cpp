#include "EntityManager.h"
#include "IP.h"
#include "Renderer.h"
#include "Ennemy.h"
#include "Level.h"
#include "Character.h"
#include "ParticleManager.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
   for(int i=0 ; i<_ennemies.size() ; i++) {
        delete _ennemies[i];
    }
    _ennemies.clear();
}

void EntityManager::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager) {
    for(int i=0 ; i<_ennemies.size() ; i++) {
        _ennemies[i]->Update(ip, eTime, level, character, *this, pManager);
        if(!_ennemies[i]->IsAlive()) {
            delete _ennemies[i];
            _ennemies.erase(_ennemies.begin() + i);
            i--;
        }
    }
}

void EntityManager::Draw(IP& ip) {
    for(int i=0 ; i<_ennemies.size() ; i++) {
        ip._renderer->Draw(*_ennemies[i]);
    }
}

void EntityManager::Add(Ennemy *e) {
    _ennemies.push_back(e);
}

void EntityManager::Clear() {
    for(int i=0 ; i<_ennemies.size() ; i++) {
        delete _ennemies[i];
    }
    _ennemies.clear();
}

int EntityManager::GetNbEnnemies() {
    return _ennemies.size();
}

Ennemy* EntityManager::GetEnnemy(int id) {
    if(id<0 || id>=_ennemies.size()) {
        return NULL;
    }
    return _ennemies[id];
}
