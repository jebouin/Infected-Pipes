#include "GameEntity.h"
#include "Map.h"

GameEntity::GameEntity(IP& ip, string name) : MovingSprite(ip, name) {
    _jumpPower = 0.7;
    _speed = 0.003;
}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Map& map) {
    SetVel(sf::Vector2f(GetVel().x / 1.2f, GetVel().y));
    Accelerate(sf::Vector2f(0, 0.003), elapsedTime);
    MovingSprite::Update(ip, elapsedTime, map);
}

void GameEntity::GoLeft(float eTime) {
    Accelerate(sf::Vector2f(-_speed, 0), eTime);
}

void GameEntity::GoRight(float eTime) {
    Accelerate(sf::Vector2f(_speed, 0), eTime);
}

void GameEntity::Jump(Map& map) {
    if(!map.IsOnGround(*this)) {
        return;
    }
    SetVel(sf::Vector2f(GetVel().x, -_jumpPower));
}
