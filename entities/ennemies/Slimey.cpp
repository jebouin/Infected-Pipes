#include "Slimey.h"
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
#include "Slime.h"

Slimey::Slimey(IP& ip, Level& level) : Ennemy(ip, "slimey", sf::IntRect(4, 0, 34, 25), 200, 100, 50, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("0", new Animation(1, 100, sf::Vector2i(0, 0), sf::Vector2i(42, 26), false));
    t.AddAnimation("1", new Animation(1, 100, sf::Vector2i(0, 26), sf::Vector2i(42, 26), false));
    t.AddAnimation("2", new Animation(1, 100, sf::Vector2i(0, 52), sf::Vector2i(42, 26), false));
    t.AddAnimation("3", new Animation(1, 100, sf::Vector2i(0, 78), sf::Vector2i(42, 26), false));
    t.SetAnimation("0");
    SetSpeed(0.002);
    SetJumpPower(.4);
    setPosition(sf::Vector2f(16*16, 20));
    _nextJump = 800;
    SetAutoDir(false);
    _prevState = 0;
}

Slimey::~Slimey() {

}

void Slimey::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    AnimationTable& t(GetAnims());

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(10+_prevState*10, 13+_prevState*10), eManager, level);
        _attackTimer.restart();
    }

    if(_jumpTimer.getElapsedTime().asMilliseconds() >= _nextJump) {
        if(Jump(level)) {
            _jumpTimer.restart();
        }
    }

    int curState = (GetHPMax()-GetHP())*4/GetHPMax();
    if(curState > _prevState && curState < 4) {
        for(int i=0 ; i<20 ; i++) {
            int type = rand()%2;
            pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                              getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 20.),
                                              MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.2, .8),
                                              MathHelper::RandFloat(-1., 1.),
                                              MathHelper::RandFloat(1000, 2000),
                                              sf::Vector2f(1, 1),
                                              sf::Vector2f(1, 1),
                                              255,
                                              0,
                                              true,
                                              true,
                                              false,
                                              type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3)));
        }
        for(int i=0 ; i<8 ; i++) {
            int type = rand()%2;
            pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle3" : "rockParticle4",
                                              getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 20.),
                                              MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.2, .8),
                                              MathHelper::RandFloat(-1., 1.),
                                              MathHelper::RandFloat(1000, 2000),
                                              sf::Vector2f(1, 1),
                                              sf::Vector2f(1, 1),
                                              255,
                                              0,
                                              true,
                                              true,
                                              false,
                                              type==0 ? sf::IntRect(2, 2, 5, 5) : sf::IntRect(2, 2, 9, 7)));
        }
        t.SetAnimation(MathHelper::IntToString(curState));
        SetSpeed(0.002 + 0.0015*curState);
        SetJumpPower(.4 + 0.1*curState);
        if(curState == 3) {
            SetSpeed(0.);
            SetJumpPower(0.);
        }
    }
    _prevState = curState;

    if(!level.GetMap().IsOnTileType(*this, Map::WALL) && !level.GetSpawner().IsOnGround(*this)) {
        if(c.x < cc.x) {
            GoRight(eTime);
        } else {
            GoLeft(eTime);
        }
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Slimey::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<80 ; i++) {
        pManager.AddParticle(new Particle(ip, "slimeParticle",
                                          getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 6.),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.2, 1.),
                                          0,
                                          MathHelper::RandFloat(1500, 2500),
                                          sf::Vector2f(1., 1.),
                                          sf::Vector2f(.0, .0),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          sf::IntRect(2, 2, 3, 3)));
    }
    for(int i=0 ; i<16 ; i++) {
        Slime *slime = new Slime(ip, level);
        slime->setPosition(getPosition());
        slime->SetVel(MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-90, -90)))*MathHelper::RandFloat(1.0, 1.2));
        eManager.Add(slime);
    }
}
