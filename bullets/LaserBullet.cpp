#include "LaserBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

LaserBullet::LaserBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "laser", sf::IntRect(0, 0, 13, 3), position, vel, 8, .5, true, ennemy, false, true, false) {
    SetCollideWithWater(false);
}

LaserBullet::~LaserBullet() {

}

void LaserBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
    SetHitbox(sf::IntRect(0, 0, getGlobalBounds().width, getGlobalBounds().height));
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void LaserBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
