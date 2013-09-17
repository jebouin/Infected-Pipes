#include "RockWorm.h"
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

RockWorm::RockWorm(IP& ip) : Ennemy(ip, "rockWorm", sf::IntRect(1, 0, 7, 19), 7, 2) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(4, 200, sf::Vector2i(0, 0), sf::Vector2i(9, 20), true));
    t.SetAnimation("idle");
    SetSpeed(0);
    SetPushable(false);
}

RockWorm::~RockWorm() {

}

bool RockWorm::AutoSpawn(IP& ip, Level& level) {
    Map& map(level.GetMap());
    bool possible = false;
    for(int i=0 ; i<map.GetSize().x ; i++) {
        for(int j=0 ; j<map.GetSize().y ; j++) {
            if(map.GetTileType(sf::Vector2i(i, j)) == Map::VOID && map.GetTileType(sf::Vector2i(i, j+1)) == Map::WALL) {
                possible = true;
            }
        }
    }
    if(!possible) {
        return false;
    }

    sf::Vector2i curPos(-1, -1);
    while(!(map.GetTileType(curPos) == Map::VOID && map.GetTileType(curPos + sf::Vector2i(0, 1)) == Map::WALL)) {
        curPos = sf::Vector2i(MathHelper::RandInt(0, map.GetSize().x), MathHelper::RandInt(0, map.GetSize().y));
    }
    SetUpperLeftCorner(sf::Vector2f(curPos.x*16+MathHelper::RandInt(0, 9), curPos.y*16+16-GetGlobalHitbox().height));
    return true;
}

void RockWorm::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager) {
    /*sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    if(c.x < cc.x) {
        GoRight(eTime);
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left+r.width+1, r.top+r.height+1)/16.f)) == Map::VOID && c.y - 20 > cc.y) {
            Jump(level);
        }
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left+r.width+1, r.top+r.height)/16.f)) == Map::WALL) {
            Jump(level);
        }
    } else if(c.x > cc.x) {
        GoLeft(eTime);
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left-1, r.top+r.height+1)/16.f)) == Map::VOID && c.y - 20 > cc.y) {
            Jump(level);
        }
        if(level.GetMap().GetTileType(sf::Vector2i(sf::Vector2f(r.left-1, r.top+r.height)/16.f)) == Map::WALL) {
            Jump(level);
        }
    }*/

    Ennemy::Update(ip, eTime, level, character, eManager, pManager);
}
