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

Turtle::Turtle(IP& ip, Level& level) : Ennemy(ip, "turtle", sf::IntRect(12, 2, 21, 18), 100, 20, 10, level) {
    AnimationTable& t(GetAnims());
    //t.AddAnimation("idle", new Animation(1, 100, sf::Vector2i(0, 0), sf::Vector2i(17, 18), true));
    t.AddAnimation("walk", new Animation(4, 200, sf::Vector2i(0, 0), sf::Vector2i(36, 21), true));
    t.SetAnimation("walk");
    SetSpeed(.0009);
    SetJumpPower(.46);
    SetWeight(1.f);
    _inLava = false;
}

Turtle::~Turtle() {

}

void Turtle::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
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
        if(c.x < cc.x) {
            GoRight(eTime);
            /*if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left+r.width+1, r.top+r.height+1)/16.f), Map::FRONT) == Map::VOID && c.y - 20 > cc.y) {
                Jump(level);
            }*/
        } else if(c.x > cc.x) {
            GoLeft(eTime);
            /*if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left-1, r.top+r.height+1)/16.f), Map::FRONT) == Map::VOID && c.y - 20 > cc.y) {
                Jump(level);
            }*/
        }
    }

    /*if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(2, 3), eManager, level);
        _attackTimer.restart();
    }

    if(level.GetMap().IsOnTileType(*this, Map::PLATFORM)) {
        if(c.y - cc.y < -10.f) {
            PlatformDrop(level);
        }
    }

    if(abs(GetVel().x) < 0.05 && MathHelper::GetVecLength(c-cc) > 16) {
        Jump(level);
    }*/

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Turtle::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    /*for(int i=0 ; i<4 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                          getPosition(),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.1, .35),
                                          MathHelper::RandFloat(-1., 1.),
                                          MathHelper::RandFloat(600, 1400),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3), false));
    }
    if(_inWater) {
        return;
    }
    for(int i=0 ; i<3 ; i++) {
        pManager.AddParticle(new Particle(ip, "smokeParticle",
                                          getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 13.),
                                          sf::Vector2f(0., 0.),
                                          MathHelper::RandFloat(-.5, .5),
                                          MathHelper::RandFloat(200, 400),
                                          sf::Vector2f(.5, .5),
                                          sf::Vector2f(2., 2.),
                                          128,
                                          0,
                                          false,
                                          false,
                                          false,
                                          sf::IntRect(2, 2, 3, 3), false));
    }*/
}
