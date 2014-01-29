#include "MachineGun.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "GunBullet.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "Level.h"

MachineGun::MachineGun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 100, 5, 7) {
    _spreadAngle = 18;
}

MachineGun::~MachineGun() {

}

void MachineGun::Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    Weapon::Update(ip, eTime, bManager, eManager, level, pManager);
}

void MachineGun::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool MachineGun::Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    if(!Weapon::Use(ip, bManager, angle, eManager, level, pManager)) {
        return false;
    }
    sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle + MathHelper::RandFloat(-_spreadAngle, _spreadAngle)));
    bManager.AddBullet(new GunBullet(ip,
                                     GetPosition(),
                                     d*MathHelper::RandFloat(0.6, 0.9),
                                     false,
                                     GetDamage()));
    ip._renderer->AddFlash(80, .1);
    return true;
}
