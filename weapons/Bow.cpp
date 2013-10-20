#include "Bow.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "Arrow.h"
#include "MathHelper.h"
#include "Renderer.h"

Bow::Bow(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 200) {

}

Bow::~Bow() {

}

void Bow::Update(IP& ip, float eTime, BulletManager& bManager) {
    Weapon::Update(ip, eTime, bManager);
}

void Bow::Draw(IP& ip) {
    Weapon::Draw(ip);
}

bool Bow::Use(IP& ip, BulletManager& bManager, float angle) {
    if(!Weapon::Use(ip, bManager, angle)) {
        return false;
    }
    /*sf::Vector2f mpos = MathHelper::GetMousePos(ip);
    sf::Vector2f d = mpos-GetPosition();
    bManager.AddBullet(new Arrow(ip,
                                 GetPosition(),
                                 d/MathHelper::GetVecLength(d)*MathHelper::RandFloat(0.7, 0.9),
                                 false));*/
    sf::Vector2f d = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle));
    bManager.AddBullet(new Arrow(ip,
                                 GetPosition(),
                                 d*MathHelper::RandFloat(0.7, 0.9),
                                 false));
    return true;
}
