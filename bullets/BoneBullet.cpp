#include "BoneBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

BoneBullet::BoneBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy)
    : Bullet(ip, "boneBullet", sf::IntRect(1, 1, 16, 5), position, vel, 30, .2, false, ennemy, true, true, false, true, false, 0) {

}

BoneBullet::~BoneBullet() {

}

void BoneBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void BoneBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
