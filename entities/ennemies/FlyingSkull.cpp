#include "FlyingSkull.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"
#include "BoneBullet.h"

FlyingSkull::FlyingSkull(IP& ip, Level& level)
    : Ennemy(ip, "flyingSkull", sf::IntRect(19, 8, 26, 17), 100, 40, 50, level) {
    AnimationTable& t(GetAnims());
    SetFlying(true);
    t.AddAnimation("idle", new Animation(4, 80, sf::Vector2i(0, 0), sf::Vector2i(64, 28), true));
    t.SetAnimation("idle");
    _boneTime = MathHelper::RandFloat(2600, 3500);
}

FlyingSkull::~FlyingSkull() {

}

void FlyingSkull::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);

    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(30, 40), eManager, level);
        _attackTimer.restart();
    }

    if(MathHelper::GetVecLength(c-cc) > 256 && MathHelper::GetVecLength(c-cc) < 600) {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
    } else {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
        Accelerate(sf::Vector2f(MathHelper::Normalize(cc-c))*0.001f, eTime);
    }

    if(_boneTimer.getElapsedTime().asMilliseconds() >= _boneTime) {
        _boneTimer.restart();
        //shoot bone!
        float dist = MathHelper::GetVecLength(getPosition()-character.getPosition());
        sf::Vector2f vec = MathHelper::Normalize(character.getPosition()-getPosition() + sf::Vector2f(0, -dist/2.5f))*.5f;
        BoneBullet *b = new BoneBullet(ip, getPosition(), vec, true);
        b->SetRotVel(rand()%2 ? MathHelper::RandFloat(-.3, -.2) : MathHelper::RandFloat(.2, .3));
        bManager.AddBullet(b);
    }
}

void FlyingSkull::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);

    /*for(int i=0 ; i<12 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, (type ? "featherParticle" : "featherParticle2",
                                          getPosition(),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(.01, .05),
                                          MathHelper::RandFloat(-0.3, 0.3),
                                          MathHelper::RandFloat(1500, 3000),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          false,
                                          true,
                                          false,
                                          sf::IntRect(3, 1, 5, 3), false));
    }*/
    for(int i=0 ; i<12 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type==0 ? sf::IntRect(1, 1, 5, 8) : sf::IntRect(1, 1, 8, 5));
        Particle *p = new Particle(ip, (type == 0 ? "skullFeather" : "skullFeather2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(-GetGlobalHitbox().width, 2*GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(.05, .1),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(800, 1200),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   false,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }
    pManager.AddParticle(new Particle(ip, "skullParticle",
                                   getPosition(),
                                   sf::Vector2f(MathHelper::RandFloat(-.1, .1), 0),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(1200, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(1, 1, 11, 5), false));
    pManager.AddParticle(new Particle(ip, "skullParticle2",
                                   getPosition(),
                                   sf::Vector2f(MathHelper::RandFloat(-.1, .1), 0),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(1200, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(1, 1, 6, 6), false));
    pManager.AddParticle(new Particle(ip, "skullParticle3",
                                   getPosition(),
                                   sf::Vector2f(MathHelper::RandFloat(-.1, .1), 0),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(1200, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(0, 0, 4, 4), false));
    pManager.AddParticle(new Particle(ip, "skullParticle4",
                                   getPosition(),
                                   sf::Vector2f(MathHelper::RandFloat(-.1, .1), 0),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(1200, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(1, 1, 5, 6), false));
}
