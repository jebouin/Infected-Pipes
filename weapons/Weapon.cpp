#include "Weapon.h"
#include "GameEntity.h"
#include "IP.h"
#include "Renderer.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "Level.h"

Weapon::Weapon(IP& ip, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime)
    : _holder(holder) {
    _baseReloadTime = reloadTime;
    _reloadTime = reloadTime;
    _relativePos = relativePos;
}

Weapon::~Weapon() {

}

void Weapon::Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    _position = _holder.GetGlobalUpperLeftPos()+_relativePos;
}

void Weapon::Draw(IP& ip) {

}

bool Weapon::Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    if(_useTimer.getElapsedTime().asMilliseconds() >= _reloadTime) {
        _useTimer.restart();
        return true;
    }
    return false;
}

sf::Vector2f Weapon::GetPosition() {
    return _position;
}

void Weapon::SetRelPosition(sf::Vector2f p) {
    _relativePos = p;
}

void Weapon::SetReloadSpeedMultiplier(float mult) {
    float curSpeed = 1000.f/_baseReloadTime;
    curSpeed *= mult;
    _reloadTime = 1000.f/curSpeed;
}
