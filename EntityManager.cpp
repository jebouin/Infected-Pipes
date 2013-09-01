#include "EntityManager.h"
#include "IP.h"
#include "Renderer.h"
#include "GameEntity.h"
#include "Map.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
    for(int i=0 ; i<_entities.size() ; i++) {
        delete _entities[i];
        _entities[i] = NULL;
    }
}

void EntityManager::Update(IP& ip, float eTime, Map& map) {
    for(int i=0 ; i<_entities.size() ; i++) {
        _entities[i]->Update(ip, eTime, map);
    }
}

void EntityManager::Draw(IP& ip) {
    for(int i=0 ; i<_entities.size() ; i++) {
        ip._renderer->Draw(*_entities[i]);
    }
}

void EntityManager::Add(GameEntity *entity) {
    _entities.push_back(entity);
}

int EntityManager::GetNbEntities() {
    return _entities.size();
}

GameEntity& EntityManager::GetEntity(int id) {
    if(id<0 || id>=_entities.size()) {
        return *_entities[0];
    }
    return *_entities[id];
}
