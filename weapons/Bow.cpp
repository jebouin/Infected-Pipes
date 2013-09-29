#include "Bow.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "MathHelper.h"

Bow::Bow(IP& ip, const GameEntity& holder) : Weapon(ip, "bow", sf::IntRect(0, 0, 7, 17), holder, sf::Vector2f(5, 4), 500) {

}

Bow::~Bow() {
    cout << "A" << endl;
}

void Bow::Update(IP& ip, float eTime, BulletManager& bManager) {
    Weapon::Update(ip, eTime, bManager);
}

void Bow::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool Bow::Use(IP& ip, BulletManager& bManager) {
    if(!Weapon::Use(ip, bManager)) {
        return false;
    }
    bManager.AddBullet(new Bullet(ip, "littleRockBullet",
                                    sf::IntRect(1, 0, 3, 4),
                                    MathHelper::GetCenter(GetGlobalHitbox()) + sf::Vector2f(0, -6),
                                    MathHelper::Ang2Vec(MathHelper::Deg2Rad(210 + MathHelper::RandFloat(-10, 10)))*MathHelper::RandFloat(0.2, 0.3),
                                    false));
    return true;
}
