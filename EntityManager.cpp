#include "EntityManager.h"
#include "IP.h"
#include "Renderer.h"
#include "Ennemy.h"
#include "Map.h"
#include "Character.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
    for(int i=0 ; i<_ennemies.size() ; i++) {
        delete _ennemies[i];
        _ennemies[i] = NULL;
    }
}

void EntityManager::Update(IP& ip, float eTime, Map& map, Character& character) {
    for(int i=0 ; i<_ennemies.size() ; i++) {
        _ennemies[i]->Update(ip, eTime, map, character, *this);
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

int EntityManager::GetNbEnnemies() {
    return _ennemies.size();
}

Ennemy* EntityManager::GetEnnemy(int id) {
    if(id<0 || id>=_ennemies.size()) {
        return NULL;
    }
    return _ennemies[id];
}
