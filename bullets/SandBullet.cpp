#include "SandBullet.h"
#include "IP.h"
#include "Character.h"
#include "ParticleManager.h"
#include "EntityManager.h"
#include "Animation.h"
#include "AnimationTable.h"

SandBullet::SandBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy)
    : Bullet(ip, "sandBullet", sf::IntRect(1, 1, 10, 6), position, vel, 10, .3, true, ennemy, false, true, false, true, false, 0.) {
    AnimationTable& anims(GetAnims());
    anims.AddAnimation("c", Animation(4, 100, sf::Vector2i(0, 0), sf::Vector2i(12, 8), true));
    anims.SetAnimation("c");
}

SandBullet::~SandBullet() {

}

void SandBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void SandBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}

bool SandBullet::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Bullet::Die(ip, pManager, eManager, level);
}
