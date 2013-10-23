#include "SnowBallEnemy.h"
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

SnowBallEnemy::SnowBallEnemy(IP& ip, Level& level) : Ennemy(ip, "snowBallEnemy", sf::IntRect(0, 0, 16, 15), 1, 1, 1, level) {
    SetSpeed(0.001);
    SetJumpPower(.0);
    SetFriction(0.f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", new Animation(8, 80, sf::Vector2i(0, 0), sf::Vector2i(16, 16), true));
    t.SetAnimation("walk");
}

SnowBallEnemy::~SnowBallEnemy() {

}

void SnowBallEnemy::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    AnimationTable& t(GetAnims());

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

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void SnowBallEnemy::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<20 ; i++) {
        pManager.AddParticle(new Particle(ip, "snowParticle",
                                          getPosition() + MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0, 8),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.05, .1),
                                          0.,
                                          MathHelper::RandFloat(600, 1400),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          sf::IntRect(1, 1, 3, 2)));
    }
}
