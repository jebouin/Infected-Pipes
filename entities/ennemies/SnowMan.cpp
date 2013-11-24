#include "SnowMan.h"
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

SnowMan::SnowMan(IP& ip, Level& level) : Ennemy(ip, "snowMan", sf::IntRect(14, 3, 18, 30), 192, 25, 30, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(4, 200, sf::Vector2i(0, 0), sf::Vector2i(45, 33), true));
    t.SetAnimation("idle");
    SetSpeed(.002);
    SetJumpPower(.46);
    SetWeight(0.6f);
}

SnowMan::~SnowMan() {

}

void SnowMan::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& t(GetAnims());
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    Map& m(level.GetMap());

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(20, 24), eManager, level);
        _attackTimer.restart();
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void SnowMan::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
}
