#include "Turtle.h"
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
#include "FireBallBullet.h"

Turtle::Turtle(IP& ip, Level& level) : Ennemy(ip, "turtle", sf::IntRect(12, 2, 21, 18), 100, 25, 30, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", new Animation(4, 200, sf::Vector2i(0, 0), sf::Vector2i(36, 21), true));
    t.AddAnimation("attack", new Animation(4, 200, sf::Vector2i(0, 21), sf::Vector2i(36, 21), false));
    t.SetAnimation("walk");
    SetSpeed(.0009);
    SetJumpPower(.46);
    SetWeight(1.f);
    _inLava = false;
    _attacking = false;
}

Turtle::~Turtle() {

}

void Turtle::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& t(GetAnims());
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    Map& m(level.GetMap());

    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& wf(level.GetWaterField(i));
        if(!wf.IsLava()) {
            continue;
        }
        if(wf.GetRect().intersects(GetGlobalHitbox())) {
            Jump(level);
            _inLava = true;
            _fireTimer.restart();
            _mPos = wf.GetRect().left + wf.GetRect().width/2.f;
            SetSpeed(.008);
        }
    }

    if(_inLava && (m.IsOnTileType(*this, Map::WALL) || level.GetSpawner().IsOnGround(*this)) && _fireTimer.getElapsedTime().asMilliseconds()>=100) {
        _inLava = false;
    }

    if(_inLava) {
         if(getPosition().x > _mPos) {
            GoRight(eTime);
        } else {
            GoLeft(eTime);
        }
    }

    if(!_inLava) {
        if(GetSpeed()>.002) {
            SetSpeed(.0009);
        }
        if(_attacking) {
            if(t.GetAnimation().IsFinished()) {
                _attacking = false;
                bManager.AddBullet(new FireBallBullet(ip,
                                                      getPosition()+sf::Vector2f((GetDir() ? 11 : -11), -5),
                                                      sf::Vector2f(GetDir() ? .1 : -.1 , MathHelper::RandFloat(-.02, .0)),
                                                      true));
                t.SetAnimation("walk");
                _fireballTimer.restart();
            }
        } else {
            if(c.x < cc.x) {
                GoRight(eTime);
            } else if(c.x > cc.x) {
                GoLeft(eTime);
            }
            if(_fireballTimer.getElapsedTime().asMilliseconds() > 1300) {
                _attacking = true;
                t.SetAnimation("attack");
            }
        }
    }

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(20, 24), eManager, level);
        _attackTimer.restart();
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Turtle::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<7 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, type==0 ? "turtleParticle" : "turtleParticle2",
                                          getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 8.),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.3, .8),
                                          MathHelper::RandFloat(-1., 1.),
                                          MathHelper::RandFloat(800, 1500),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          type==0 ? sf::IntRect(1, 2, 4, 4) : sf::IntRect(1, 1, 7, 7), false));
    }
    for(int i=0 ; i<3 ; i++) {
        Particle* p = new Particle(ip, "explosion",
                                  getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0, 12),
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
        p->GetAnims().AddAnimation("base", new Animation(7, 40, sf::Vector2i(0, 0), sf::Vector2i(13, 13), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
    pManager.AddParticle(new Particle(ip, "turtleHead",
                                      getPosition()+sf::Vector2f((GetDir() ? 11 : -11), -5),
                                      sf::Vector2f((GetDir() ? 1 : -1)*.2, -.2),
                                      MathHelper::RandFloat(-.2, .2),
                                      MathHelper::RandFloat(2000, 2300),
                                      sf::Vector2f(1, 1),
                                      sf::Vector2f(1, 1),
                                      255,
                                      0,
                                      true,
                                      true,
                                      false,
                                      sf::IntRect(1, 1, 4, 4), false));
    if(_inWater) {
        return;
    }
    for(int i=0 ; i<5 ; i++) {
        pManager.AddParticle(new Particle(ip, "smokeParticle",
                                          getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 17.),
                                          sf::Vector2f(0., 0.),
                                          MathHelper::RandFloat(-.5, .5),
                                          MathHelper::RandFloat(300, 600),
                                          sf::Vector2f(.5, .5),
                                          sf::Vector2f(2., 2.),
                                          180,
                                          0,
                                          false,
                                          false,
                                          false,
                                          sf::IntRect(2, 2, 3, 3), false));
    }
}
