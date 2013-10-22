#include "Weapon.h"
#include "GameEntity.h"
#include "IP.h"
#include "Renderer.h"
#include "BulletManager.h"
#include "Bullet.h"

Weapon::Weapon(IP& ip, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime)
    : _holder(holder) {
    _reloadTime = reloadTime;
    _relativePos = relativePos;
}

Weapon::~Weapon() {

}

void Weapon::Update(IP& ip, float eTime, BulletManager& bManager) {
    _position = _holder.GetGlobalUpperLeftPos()+_relativePos;
}

void Weapon::Draw(IP& ip) {

}

bool Weapon::Use(IP& ip, BulletManager& bManager, float angle) {
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
