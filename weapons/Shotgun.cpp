#include "Shotgun.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "GunBullet.h"
#include "MathHelper.h"
#include "Renderer.h"

Shotgun::Shotgun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 500) {

}

Shotgun::~Shotgun() {

}

void Shotgun::Update(IP& ip, float eTime, BulletManager& bManager) {
    Weapon::Update(ip, eTime, bManager);
}

void Shotgun::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool Shotgun::Use(IP& ip, BulletManager& bManager, float angle) {
    if(!Weapon::Use(ip, bManager, angle)) {
        return false;
    }
    for(int i=0 ; i<8 ; i++) {
        sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle + MathHelper::RandFloat(-20, 20)));
        bManager.AddBullet(new GunBullet(ip,
                                     GetPosition(),
                                     d*MathHelper::RandFloat(0.6, 0.9),
                                     false));
    }
    ip._renderer->AddFlash(80, .2);
    return true;
}
