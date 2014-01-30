#include "GunBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "Particle.h"

GunBullet::GunBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy, float damage) : Bullet(ip, "bullet", sf::IntRect(0, 0, 4, 4), position, vel, damage, .1, true, ennemy, false, true, false, true, false, 0) {
    AnimationTable& anims(GetAnims());
    anims.AddAnimation("c", Animation(7, 50, sf::Vector2i(0, 0), sf::Vector2i(4, 4), true));
    anims.SetAnimation("c");
}

GunBullet::~GunBullet() {

}

void GunBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void GunBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
