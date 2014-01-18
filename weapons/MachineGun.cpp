#include "MachineGun.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "GunBullet.h"
#include "MathHelper.h"
#include "Renderer.h"

MachineGun::MachineGun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 1) {

}

MachineGun::~MachineGun() {

}

void MachineGun::Update(IP& ip, float eTime, BulletManager& bManager) {
    Weapon::Update(ip, eTime, bManager);
}

void MachineGun::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool MachineGun::Use(IP& ip, BulletManager& bManager, float angle) {
    if(!Weapon::Use(ip, bManager, angle)) {
        return false;
    }
    sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle + MathHelper::RandFloat(-6, 6)));
    bManager.AddBullet(new GunBullet(ip,
                                     GetPosition(),
                                     d*MathHelper::RandFloat(0.6, 0.9),
                                     false));
    ip._renderer->AddFlash(80, .1);
    return true;
}
