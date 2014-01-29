#include "Missile.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"

Missile::Missile(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy)
    : Bullet(ip, "missile", sf::IntRect(1, 1, 6, 6), position, vel, 160, .5, true, ennemy, false, true, true, true, false, 0) {
    _prevPos = getPosition();
}

Missile::~Missile() {

}

void Missile::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    if(!IsDying()) {
        setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
        SetHitbox(sf::IntRect(0, 0, getGlobalBounds().width, getGlobalBounds().height));
    }
    //turn here
    float angle = MathHelper::Vec2Ang(GetVel());
    float angleToChar = MathHelper::Vec2Ang(character.getPosition() - getPosition());
    if(angle < 0) {
        angle += 2.f*PI;
    }
    if(angleToChar < 0) {
        angleToChar += 2.f*PI;
    }
    static const float angleSpeed = .003;
    float delta = angleToChar-angle;
    if(delta >= 0) {
        if(delta > PI) {
            angle -= angleSpeed*eTime;
        } else {
            angle += angleSpeed*eTime;
        }
    } else {
        if(delta > -PI) {
            angle -= angleSpeed*eTime;
        } else {
            angle += angleSpeed*eTime;
        }
    }
    SetVel(MathHelper::Ang2Vec(angle) * MathHelper::GetVecLength(GetVel()));

    Bullet::Update(ip, eTime, level, character, pManager, eManager);

    float pTime = MathHelper::GetVecLength(getPosition()-_prevPos);
    for(int i=0 ; i<pTime ; i+=4) {
        float intx = float(i)/pTime;
        sf::Vector2f basePos = (getPosition() - _prevPos)*intx + _prevPos;
        Particle *p = new Particle(ip,
                                   "missileSmoke",
                                   getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360)))*MathHelper::RandFloat(0, 3),
                                   sf::Vector2f(0, 0),
                                   0,
                                   MathHelper::RandFloat(600, 900),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255, 0,
                                   false, false, false, sf::IntRect(0, 0, 4, 4), false);
        pManager.AddParticle(p);
        p = 0;
    }
    _prevPos = getPosition();
}

void Missile::Draw(IP& ip) {
    Bullet::Draw(ip);
}

bool Missile::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Bullet::Die(ip, pManager, eManager, level);

    Particle *p = new Particle(ip,
                               "bigExplosion",
                               getPosition(),
                               sf::Vector2f(0, 0),
                               0,
                               160,
                               sf::Vector2f(1, 1),
                               sf::Vector2f(1, 1),
                               255, 255,
                               false, false, true, sf::IntRect(2, 2, 21, 21), false);
    p->GetAnims().AddAnimation("explosion", Animation(8, 20, sf::Vector2i(0, 0), sf::Vector2i(25, 25), false));
    p->GetAnims().SetAnimation("explosion");
    pManager.AddParticle(p);
    p = 0;
}
