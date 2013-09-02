#include "GameEntity.h"
#include "Map.h"
#include "MathHelper.h"
#include "EntityManager.h"

GameEntity::GameEntity(IP& ip, string name, sf::IntRect hitbox) : MovingSprite(ip, name, hitbox) {
    _jumpPower = 0.7;
    _speed = 0.003;
    _weight = 0.05;
}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Map& map, EntityManager& eManager) {
    SetVel(sf::Vector2f(GetVel().x / 1.2f, GetVel().y));
    Accelerate(sf::Vector2f(0, 0.003), elapsedTime);

    for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
        Ennemy* e = eManager.GetEnnemy(i);
        if((GameEntity*)(e) == this) {
            continue;
        }
        //if(MathHelper::ABS(e.getPosition().x-getPosition().x) > 42)
        Collide((GameEntity*)e);
    }

    MovingSprite::Update(ip, elapsedTime, map);
}

void GameEntity::Collide(GameEntity* other) {
    sf::FloatRect r = getGlobalBounds();
    sf::FloatRect r2 = other->getGlobalBounds();
    if(!r.intersects(r2)) {
        return;
    }
    sf::Vector2f dist = /*MathHelper::ABS(*/getPosition()-other->getPosition()/*)*/;
    float rx = (r.width/2.f + r2.width/2.f - dist.x) / (r.width/2.f + r2.width/2.f);
    float dx = rx*MathHelper::SGN(dist.x);
    float ry = (r.height/2.f + r2.height/2.f - dist.y) / (r.height/2.f + r2.height/2.f);
    float dy = ry*MathHelper::SGN(dist.y);

    SetVel(GetVel() + sf::Vector2f(dx, 0)*other->GetWeight());
    other->SetVel(other->GetVel() - sf::Vector2f(dx, 0)*GetWeight());
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

void GameEntity::SetJumpPower(float p) {
    _jumpPower = p;
}

void GameEntity::SetSpeed(float s) {
    _speed = s;
}

void GameEntity::SetWeight(float w) {
    _weight = w;
}

float GameEntity::GetWeight() {
    return _weight;
}
