#include "MissileBall.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"
#include "WaterField.h"
#include "Missile.h"

MissileBall::MissileBall(IP& ip, Level& level)
    : Ennemy(ip, "missileBall", sf::IntRect(2, 2, 17, 17), 200, 30, 40, level) {
    AnimationTable& anims(GetAnims());
    anims.AddAnimation("idle", new Animation(4, 100, sf::Vector2i(0, 0), sf::Vector2i(21, 21), true));
    anims.AddAnimation("prepare", new Animation(2, 200, sf::Vector2i(0, 21), sf::Vector2i(21, 21), true));
    anims.AddAnimation("attacked", new Animation(1, 1000, sf::Vector2i(0, 42), sf::Vector2i(21, 21), false));
    anims.SetAnimation("idle");
    SetFlying(true);
    SetPhysics(true);
    _attackTime = 800;
    _missileTime = 1000;
}

MissileBall::~MissileBall() {

}

void MissileBall::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& anims(GetAnims());
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
    sf::Vector2f dirToPlayer = MathHelper::Normalize(character.getPosition() - getPosition());
    string curAnim = anims.GetAnimationName();

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
        if(_attackTimer.getElapsedTime().asMilliseconds() > _attackTime) {
            character.Damage(MathHelper::RandInt(30, 35), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), dirToPlayer*MathHelper::RandFloat(.1, .2), eManager, level);
            _attackTimer.restart();
        }
        character.Accelerate(dirToPlayer*0.01f, eTime);
    }

    if(_missileTimer.getElapsedTime().asMilliseconds() > _missileTime) {
        _missileTime = MathHelper::RandFloat(3000, 4000);
        _missileTimer.restart();
        _prepareTimer.restart();
        anims.SetAnimation("prepare");
    }
    if(curAnim == "idle") {
        Accelerate(sf::Vector2f(dirToPlayer*.001f), eTime);
    } else if(curAnim == "prepare") {
        if(_prepareTimer.getElapsedTime().asMilliseconds() > 1000) {
            anims.SetAnimation("attacked");
            //FIRE MISSILES!!!
            for(int i=0 ; i<4 ; i++) {
                float angle = 45.f + i*90.f;
                bManager.AddBullet(new Missile(ip, getPosition(), MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle))*MathHelper::RandFloat(0.18, 0.27), true));
            }
        }
    } else if(curAnim == "attacked") {
        if(anims.GetAnimation().IsFinished()) {
            anims.SetAnimation("idle");
        }
    }
}

void MissileBall::Draw(IP& ip) {
    Ennemy::Draw(ip);
}

void MissileBall::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);

    /*for(int i=0 ; i<8 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 6, 5) : sf::IntRect(1, 1, 8, 8));
        Particle *p = new Particle(ip, (type == 0 ? "snowRockParticle" : "snowRockParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.2, .5),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(800, 1200),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }
    for(int i=0 ; i<4 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 7, 8) : sf::IntRect(1, 1, 7, 10));
        Particle *p = new Particle(ip, (type == 0 ? "fingerParticle" : "fingerParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.4, .6),
                                   MathHelper::RandFloat(-.3, .3),
                                   MathHelper::RandFloat(1000, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }*/
}
