#include "Bow.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "Arrow.h"
#include "MathHelper.h"
#include "Renderer.h"

Bow::Bow(IP& ip, const GameEntity& holder) : Weapon(ip, "bow", sf::IntRect(0, 0, 7, 17), holder, sf::Vector2f(5, 4), 500) {

}

Bow::~Bow() {

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
    sf::Vector2f mpos = sf::Vector2f(ip._renderer->GetTexture().convertCoords(sf::Vector2i(MathHelper::GetMousePos(*ip._window))));
    sf::Vector2f d = mpos-getPosition();
    bManager.AddBullet(new Arrow(ip,
                                  getPosition(),
                                  d/MathHelper::GetVecLength(d)*MathHelper::RandFloat(0.5, 0.6),
                                  false));
    return true;
}
