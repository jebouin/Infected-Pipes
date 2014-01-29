#include "Rifle.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "GunBullet.h"
#include "MathHelper.h"
#include "Renderer.h"

Rifle::Rifle(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 600, 10, 14) {

}

Rifle::~Rifle() {

}

void Rifle::Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    Weapon::Update(ip, eTime, bManager, eManager, level, pManager);
}

void Rifle::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool Rifle::Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    if(!Weapon::Use(ip, bManager, angle, eManager, level, pManager)) {
        return false;
    }
    sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle + MathHelper::RandFloat(-3, 3)));
    bManager.AddBullet(new GunBullet(ip,
                                     GetPosition(),
                                     d*MathHelper::RandFloat(0.7, 1.0),
                                     false,
                                     GetDamage()));
    ip._renderer->AddFlash(80, .2);
    return true;
}
