#include "GameEntity.h"
#include "Map.h"

GameEntity::GameEntity(IP& ip, string name) : MovingSprite(ip, name) {

}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Map& map) {
    SetVel(GetVel() / 1.05f);
    MovingSprite::Update(ip, elapsedTime, map);
}
