#include "FireBall.h"
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

FireBall::FireBall(IP& ip, Level& level) : Ennemy(ip, "fireBall", sf::IntRect(1, 1, 14, 14), 20, 10, 20, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", Animation(6, 50, sf::Vector2i(0, 0), sf::Vector2i(20, 16), true));
    t.SetAnimation("idle");
    SetCollideOnPlatform(false);
    SetFriction(.0);
    SetPhysics(false);
    _jumping = false;
}

FireBall::~FireBall() {

}

bool FireBall::AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character) {
    Map& m(level.GetMap());
    std::vector<WaterField*> lf;
    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& wf(level.GetWaterField(i));
        if(wf.IsSurface()) {
            continue;
        }
        if(wf.IsLava() && m.GetNbNeighbours(sf::Vector2i(MathHelper::GetCenter(wf.GetRect())/16.f), Map::FRONT)==8) {
            lf.push_back(&wf);
        }
    }
    if(lf.size()==0) {
        return false;
    }
    setPosition(MathHelper::GetCenter(lf[rand()%lf.size()]->GetRect()));
    return true;
}

void FireBall::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    Map& m(level.GetMap());

    //get the lava below
    float highest = 42000000;
    int bid = -42;
    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& wf(level.GetWaterField(i));
        if(!wf.IsLava() || !wf.IsSurface()) {
            continue;
        }
        if(wf.GetRect().left < getPosition().x && wf.GetRect().left+wf.GetRect().width>getPosition().x) {
            if(wf.GetRect().top < highest) {
                highest = wf.GetRect().top;
                bid = i;
            }
        }
    }
    if(bid!=-42) {
        WaterField& belowWf(level.GetWaterField(bid));
        if(!_jumping && _jumpTimer.getElapsedTime().asMilliseconds() >= 500 && _inWater) {
            _jumping = true;
            sf::FloatRect bwfr(belowWf.GetRect());
            if(getPosition().x-bwfr.left < 150.f) {
                SetVel(sf::Vector2f(MathHelper::RandFloat(.0f, .07f), -.4f));
            } else if(bwfr.left+bwfr.width-getPosition().x < 150.f) {
                SetVel(sf::Vector2f(MathHelper::RandFloat(-.07f, .0f), -.4f));
            } else {
                SetVel(sf::Vector2f(MathHelper::RandFloat(-.07f, .07f), -.4f));
            }
            SetCollideWithWater(false);
            setPosition(getPosition() + sf::Vector2f(0, -15));
        }
    }

    if(_inWater && _jumping) {
        _jumpTimer.restart();
        _jumping = false;
    }

    if(GetVel().y > 0) {
        SetCollideWithWater(true);
        WaterCollision(level, GetVel()*eTime, pManager, ip);
    }

    if(_inWater && !_jumping) {
        SetPhysics(true);
    } else {
        SetPhysics(false);
        Accelerate(sf::Vector2f(0, .0006), eTime);
    }

    if(!_inWater && (m.IsCollided(*this, Map::WALL) || level.GetSpawner().IsCollided(*this))) {
        _jumping = false;
        SetPhysics(false);
        SetCollideWithWater(true);
        SetVel(sf::Vector2f(0, 0));
        //Die(ip, pManager, eManager, level);
        SpreadParticles(ip, pManager);
        SetAlive(false);
    }

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
        sf::Vector2f forceDir(MathHelper::Normalize(character.getPosition()-getPosition()));
        if(_attackTimer.getElapsedTime().asMilliseconds() >= 400) {
            character.Damage(MathHelper::RandInt(20, 25), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), forceDir * MathHelper::RandFloat(.4, .6), eManager, level);
            _attackTimer.restart();
        }
        character.Accelerate(forceDir*0.01f, eTime);
    }

    setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void FireBall::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    SpreadParticles(ip, pManager);
}

void FireBall::SpreadParticles(IP& ip, ParticleManager& pManager) {
    for(int i=0 ; i<12 ; i++) {
        pManager.AddParticle(new Particle(ip, "fireParticle",
                                          getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0, 5),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(.1, .35),
                                          0.f,
                                          MathHelper::RandFloat(100, 200),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          false,
                                          true,
                                          false,
                                          sf::IntRect(1, 1, 3, 3), false));
    }
    for(int i=0 ; i<3 ; i++) {
        Particle* p = new Particle(ip, "fireParticle2",
                                  getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0, 5),
                                  MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(.01, .05),
                                  MathHelper::RandFloat(-.1, .1),
                                  240,
                                  sf::Vector2f(1, 1),
                                  sf::Vector2f(1, 1),
                                  255,
                                  255,
                                  false,
                                  true,
                                  true,
                                  sf::IntRect(1, 1, 5, 5), false);
        p->GetAnims().AddAnimation("base", Animation(4, 60, sf::Vector2i(0, 0), sf::Vector2i(7, 7), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
    for(int i=0 ; i<3 ; i++) {
        Particle* p = new Particle(ip, "explosion",
                                  getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0, 8),
                                  sf::Vector2f(0, 0),
                                  0,
                                  280,
                                  sf::Vector2f(1, 1),
                                  sf::Vector2f(1, 1),
                                  255,
                                  255,
                                  false,
                                  false,
                                  true,
                                  sf::IntRect(42, 42, 42, 42), false);
        p->GetAnims().AddAnimation("base", Animation(7, 40, sf::Vector2i(0, 0), sf::Vector2i(13, 13), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
}
