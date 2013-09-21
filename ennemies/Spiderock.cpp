#include "Spiderock.h"
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

Spiderock::Spiderock(IP& ip) : Ennemy(ip, "spiderock", sf::IntRect(3, 0, 13, 18), 10, 1) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(1, 100, sf::Vector2i(0, 0), sf::Vector2i(17, 18), true));
    t.AddAnimation("walk", new Animation(4, 100, sf::Vector2i(0, 18), sf::Vector2i(17, 18), true));
    t.SetAnimation("walk");
    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
}

Spiderock::~Spiderock() {

}

void Spiderock::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    if(c.x < cc.x) {
        GoRight(eTime);
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left+r.width+1, r.top+r.height+1)/16.f)) == Map::VOID && c.y - 20 > cc.y) {
            Jump(level);
        }
    } else if(c.x > cc.x) {
        GoLeft(eTime);
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left-1, r.top+r.height+1)/16.f)) == Map::VOID && c.y - 20 > cc.y) {
            Jump(level);
        }
    }

    if(abs(GetVel().x) < 0.02 && MathHelper::GetVecLength(c-cc) > 16) {
        Jump(level);
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager);
}