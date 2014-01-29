#include "GroundAttackBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "Particle.h"

GroundAttackBullet::GroundAttackBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy, float damage, float penetration, bool big)
: Bullet(ip,
         (big ? "bigGroundAttackBullet" : "groundAttackBullet"),
         (big ? sf::IntRect(0, 0, 16, 22) : sf::IntRect(0, 0, 9, 12)), position, vel, damage, .9, true, ennemy, false, true, false, true, false, penetration) {

    if(!big) {
        AnimationTable& anims(GetAnims());
        anims.AddAnimation("i'matreeyourenothaha", Animation(2, 200, sf::Vector2i(0, 0), sf::Vector2i(9, 12), true));
        anims.SetAnimation("i'matreeyourenothaha");
    }
}

GroundAttackBullet::~GroundAttackBullet() {

}

void GroundAttackBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void GroundAttackBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
