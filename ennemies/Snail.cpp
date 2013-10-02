#include "Snail.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"

Snail::Snail(IP& ip) : Ennemy(ip, "snail", sf::IntRect(3, 1, 23, 19), 42, 8, 6) {
    /*AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(1, 100, sf::Vector2i(0, 0), sf::Vector2i(17, 18), true));
    t.AddAnimation("walk", new Animation(4, 100, sf::Vector2i(0, 18), sf::Vector2i(17, 18), true));
    t.SetAnimation("walk");*/
    SetSpeed(MathHelper::RandFloat(0.0003, 0.0004));
}

Snail::~Snail() {

}

void Snail::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0));
        _attackTimer.restart();
    }

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
