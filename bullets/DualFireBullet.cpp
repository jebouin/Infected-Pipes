#include "DualFireBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

DualFireBullet::DualFireBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy)
    : Bullet(ip, "dualFireBullet", sf::IntRect(1, 1, 8, 5), position, vel, 42, .6, true, ennemy, false, true, false, true, false, 0) {

}

DualFireBullet::~DualFireBullet() {

}

void DualFireBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
    SetHitbox(sf::IntRect(0, 0, getGlobalBounds().width, getGlobalBounds().height));
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void DualFireBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
