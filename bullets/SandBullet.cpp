#include "SandBullet.h"
#include "IP.h"
#include "Character.h"
#include "ParticleManager.h"
#include "EntityManager.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "MathHelper.h"
#include "Particle.h"

SandBullet::SandBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy)
    : Bullet(ip, "sandBullet", sf::IntRect(1, 0, 10, 5), position, vel, 10, .3, true, ennemy, false, true, false, true, false, 0.) {
    AnimationTable& anims(GetAnims());
    anims.AddAnimation("c", Animation(4, 100, sf::Vector2i(0, 0), sf::Vector2i(12, 8), true));
    anims.SetAnimation("c");
}

SandBullet::~SandBullet() {

}

void SandBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
    if(MathHelper::ABS(GetVel().x) < .008) {
        Die(ip, pManager, eManager, level);
    }
}

void SandBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}

bool SandBullet::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Bullet::Die(ip, pManager, eManager, level);

    for(int i=0 ; i<16 ; i++) {
        float frameTime = MathHelper::RandFloat(60, 140);
        Particle *p = new Particle(ip, "sandParticle", getPosition(), MathHelper::RandDirVector()*MathHelper::RandFloat(.08, .12),
                                   0, frameTime*3, sf::Vector2f(1, 1), sf::Vector2f(1, 1), 255, 120, false, false, true, sf::IntRect(0, 0, 4, 4), true);
        p->GetAnims().AddAnimation("c", Animation(3, frameTime, sf::Vector2i(0, 0), sf::Vector2i(4, 4), false));
        p->GetAnims().SetAnimation("c");
        pManager.AddParticle(p);
    }
}
