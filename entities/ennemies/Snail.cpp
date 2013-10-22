#include "Snail.h"
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
#include "LaserBullet.h"
#include "Renderer.h"

Snail::Snail(IP& ip, Level& level) : Ennemy(ip, "snail", sf::IntRect(3, 1, 26, 19), 42, 8, 6, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", new Animation(2, 200, sf::Vector2i(0, 0), sf::Vector2i(31, 21), true));
    t.AddAnimation("prepare", new Animation(4, 250, sf::Vector2i(0, 21), sf::Vector2i(31, 21), false));
    t.AddAnimation("explode", new Animation(2, 150, sf::Vector2i(0, 42), sf::Vector2i(20, 16), true));
    t.SetAnimation("walk");
    SetSpeed(MathHelper::RandFloat(0.0003, 0.0004));
    _preparing = false;
    _nextAttack = MathHelper::RandFloat(1000, 3000);
    SetWeight(1.0);
    SetCollisionPrecision(.05);

    _circle.setFillColor(sf::Color(0, 0, 0, 0));
    _circle.setOutlineColor(sf::Color(220, 200, 255));
    _circle.setOutlineThickness(1);
    _circle.setPointCount(42);
}

Snail::~Snail() {

}

void Snail::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    AnimationTable& t(GetAnims());
    float attackTime = _attackTimer.getElapsedTime().asMilliseconds();
    sf::Vector2f eyePos = GetGlobalUpperLeftPos() + sf::Vector2f(GetDir() ? GetAnims().GetAnimation().GetRect().width-4. : 3., 1.);

    if(t.GetAnimationName() != "explode") {
        if(!_preparing) {
            if(attackTime >= _nextAttack) {
                _preparing = true;
                _attackTimer.restart();
                t.SetAnimation("prepare");
            }
        } else {
            if(attackTime >= 1000) {
                _preparing = false;
                _attackTimer.restart();
                t.SetAnimation("walk");
                _nextAttack = MathHelper::RandFloat(1000, 3000);

                //shoot
                bManager.AddBullet(new LaserBullet(ip,
                                                eyePos,
                                                -MathHelper::Normalize(eyePos - cc)*0.4f,
                                                true));
            }
            UpdateCircle(eyePos);
        }

        /*if(!IsAlive()) {
            //SetRotVel(0.1f);
            _explodeTimer.restart();
            SetInvincible(true);
            SetAlive(true);
            SetHitbox(sf::IntRect(3, 2, 13, 13));
            t.SetAnimation("explode");
            SetSpeed(GetSpeed() * 4.f);
            _preparing = false;
            setOrigin(MathHelper::GetCenter(sf::FloatRect(GetHitbox())));
        }*/
    }

    if(!_preparing) {
        if(c.x < cc.x) {
            GoRight(eTime);
        } else if(c.x > cc.x) {
            GoLeft(eTime);
        }

        if(level.GetMap().IsOnTileType(*this, Map::PLATFORM)) {
            if(c.y - cc.y < -10.f) {
                PlatformDrop(level);
            }
        }
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);

    if(t.GetAnimationName() == "explode" && _explodeTimer.getElapsedTime().asMilliseconds() >= 2000) {
        SetAlive(false);
    }
}

void Snail::Draw(IP& ip) {
    Ennemy::Draw(ip);
    if(_preparing) {
        ip._renderer->Draw(_circle);
    }
}

void Snail::UpdateCircle(sf::Vector2f eyePos) {
    float attackTime = _attackTimer.getElapsedTime().asMilliseconds();
    _circle.setOrigin(sf::Vector2f(_circle.getRadius(), _circle.getRadius()));
    _circle.setPosition(eyePos);
    float p = attackTime/1000.0;
    _circle.setRotation(p*360.f);
    sf::Color color = _circle.getOutlineColor();
    _circle.setRadius(20.0 - (1.0/p+1.)*10.0);
    _circle.setOutlineColor(sf::Color(color.r, color.g, color.b, p*255));
}

void Snail::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<12 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, type==0 ? "snailParticle" : "snailParticle2",
                                          getPosition(),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.2, .8),
                                          MathHelper::RandFloat(-1., 1.),
                                          MathHelper::RandFloat(600, 1400),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          type==0 ? sf::IntRect(2, 2, 7, 3) : sf::IntRect(2, 2, 5, 4)));
    }
    if(_inWater) {
        return;
    }
    for(int i=0 ; i<4 ; i++) {
        pManager.AddParticle(new Particle(ip, "smokeParticle",
                                          sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                          sf::Vector2f(0., 0.),
                                          MathHelper::RandFloat(-.5, .5),
                                          MathHelper::RandFloat(400, 700),
                                          sf::Vector2f(.5, .5),
                                          sf::Vector2f(2., 2.),
                                          128,
                                          0,
                                          false,
                                          false,
                                          false,
                                          sf::IntRect(2, 2, 3, 3)));
    }
}
