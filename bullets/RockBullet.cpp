#include "RockBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

RockBullet::RockBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "littleRockBullet", sf::IntRect(1, 0, 3, 4), position, vel, 2, .2, true, ennemy, true, false, false, true, true) {

}

RockBullet::~RockBullet() {

}

void RockBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
    if(MathHelper::GetVecLength(GetVel()) < 0.1) {
        Die();
    }
}

void RockBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
