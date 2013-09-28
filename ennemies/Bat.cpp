#include "Bat.h"
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

Bat::Bat(IP& ip) : Ennemy(ip, "bat", sf::IntRect(11, 1, 14, 11), 20, 3, 3) {
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

    if(MathHelper::GetVecLength(c-cc) > 142) {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
    } else {
        Accelerate(sf::Vector2f(MathHelper::RandFloat(-0.003, 0.003), MathHelper::RandFloat(-0.002, 0.002)), eTime);
        Accelerate(sf::Vector2f(MathHelper::Normalize(cc-c))*0.001f, eTime);
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}
