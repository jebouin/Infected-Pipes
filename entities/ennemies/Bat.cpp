#include "Bat.h"
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

Bat::Bat(IP& ip, Level& level) : Ennemy(ip, "bat", sf::IntRect(11, 1, 14, 11), 20, 3, 3, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("flying", new Animation(4, 100, sf::Vector2i(0, 0), sf::Vector2i(36, 13), true));
    t.SetAnimation("flying");

    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
    SetFlying(true);
    SetCollideOnPlatform(false);
}

Bat::~Bat() {

}

void Bat::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(4, 5), eManager, level);
        _attackTimer.restart();
    }

    if(MathHelper::GetVecLength(c-cc) > 142 && MathHelper::GetVecLength(c-cc) < 600) {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
    } else {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
        Accelerate(sf::Vector2f(MathHelper::Normalize(cc-c))*0.001f, eTime);
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Bat::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    GameEntity::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<6 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, "featherParticle",
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
                                          sf::IntRect(3, 1, 5, 3)));
    }
}
