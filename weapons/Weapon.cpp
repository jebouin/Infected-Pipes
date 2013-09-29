#include "Weapon.h"
#include "GameEntity.h"
#include "IP.h"
#include "Renderer.h"
#include "BulletManager.h"
#include "Bullet.h"

Weapon::Weapon(IP& ip, string name, sf::IntRect hitbox, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime)
    : MovingSprite(ip, name, true), _holder(holder) {
    _reloadTime = reloadTime;
    _relativePos = relativePos;
}

Weapon::~Weapon() {

}

void Weapon::Update(IP& ip, float eTime, BulletManager& bManager) {
    setPosition(_holder.getPosition() + _relativePos);
    MovingSprite::Update(ip, eTime);
}

void Weapon::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}

bool Weapon::Use(IP& ip, BulletManager& bManager) {
    if(_useTimer.getElapsedTime().asMilliseconds() >= _reloadTime) {
        _useTimer.restart();
        return true;
    }
    return false;
}
