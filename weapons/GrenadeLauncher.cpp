#include "GrenadeLauncher.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "Grenade.h"
#include "MathHelper.h"
#include "Renderer.h"

GrenadeLauncher::GrenadeLauncher(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 500) {

}

GrenadeLauncher::~GrenadeLauncher() {

}

void GrenadeLauncher::Update(IP& ip, float eTime, BulletManager& bManager) {
    Weapon::Update(ip, eTime, bManager);
}

void GrenadeLauncher::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool GrenadeLauncher::Use(IP& ip, BulletManager& bManager, float angle) {
    if(!Weapon::Use(ip, bManager, angle)) {
        return false;
    }
    sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle));
    bManager.AddBullet(new Grenade(ip,
                                   GetPosition(),
                                   d*.5f,
                                   false));
    return true;
}
