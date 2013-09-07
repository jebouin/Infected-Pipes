#include "GameEntity.h"
#include "Level.h"
#include "Map.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"

GameEntity::GameEntity(IP& ip, string name, sf::IntRect hitbox, int hp) : MovingSprite(ip, name, hitbox) {
    _jumpPower = 0.7;
    _speed = 0.003;
    _weight = 0.3;
    _alive = true;
    _hpMax = hp;
    _hp = _hpMax;
}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager) {
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

    MovingSprite::Update(ip, elapsedTime, level);
}

void GameEntity::Update(IP& ip, float elapsedTime) {
    MovingSprite::Update(ip, elapsedTime);
}

void GameEntity::Collide(GameEntity* other) {
    sf::FloatRect r = GetGlobalHitbox();
    sf::FloatRect r2 = other->GetGlobalHitbox();
    if(!r.intersects(r2)) {
        return;
    }
    sf::Vector2f c = MathHelper::GetCenter(r);
    sf::Vector2f c2 = MathHelper::GetCenter(r2);
    sf::Vector2f dist = MathHelper::ABS(sf::Vector2f(c-c2));
    float rx = (r.width/2.f + r2.width/2.f - dist.x) / (r.width/2.f + r2.width/2.f);
    float dx = rx*MathHelper::SGN(sf::Vector2f(c-c2).x);

    SetVel(GetVel() + sf::Vector2f(dx, 0)*other->GetWeight());
    other->SetVel(other->GetVel() - sf::Vector2f(dx, 0)*GetWeight());
}

void GameEntity::GoLeft(float eTime) {
    Accelerate(sf::Vector2f(-_speed, 0), eTime);
}

void GameEntity::GoRight(float eTime) {
    Accelerate(sf::Vector2f(_speed, 0), eTime);
}

void GameEntity::Jump(Level& level) {
    if(!level.GetSpawner().IsOnGround(*this) && !level.GetMap().IsOnGround(*this)) {
        return;
    }
    SetVel(sf::Vector2f(GetVel().x, -_jumpPower));
}

void GameEntity::Damage(int dmg) {
    _hp -= dmg;
        if(_hp <= 0) {
        _alive = false;
    }
}

void GameEntity::Hit(GameEntity *other) {
    other->Damage(5);
    sf::Vector2f c(MathHelper::GetCenter(GetGlobalHitbox()));
    sf::Vector2f oc(MathHelper::GetCenter(other->GetGlobalHitbox()));
    sf::Vector2f dir = MathHelper::Normalize(sf::Vector2f(oc.x-c.x, 0));
    other->SetVel(other->GetVel() + sf::Vector2f(dir.x, 0)*0.07f/other->GetWeight());
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

bool GameEntity::IsAlive() {
    return _alive;
}

int GameEntity::GetHp() {
    return _hp;
}

int GameEntity::GetHpMax() {
    return _hpMax;
}
