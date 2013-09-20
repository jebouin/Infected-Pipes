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
    t.AddAnimation("spawn", new Animation(4, 60, sf::Vector2i(0, 0), sf::Vector2i(9, 20), false));
    t.AddAnimation("idle", new Animation(4, 200, sf::Vector2i(0, 20), sf::Vector2i(9, 20), true));
    t.AddAnimation("despawn", new Animation(4, 60, sf::Vector2i(0, 60), sf::Vector2i(9, 20), false));
    t.SetAnimation("spawn");
    SetSpeed(0);
    SetPushable(false);
    _outTime = MathHelper::RandFloat(3000, 8000);
}

RockWorm::~RockWorm() {

}

bool RockWorm::AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character) {
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

    bool correctPos = false;
    while(!correctPos) {
        correctPos = true;
        sf::Vector2i curPos(-1, -1);
        while(!(map.GetTileType(curPos) == Map::VOID && map.GetTileType(curPos + sf::Vector2i(0, 1)) == Map::WALL)) {
            curPos = sf::Vector2i(MathHelper::RandInt(0, map.GetSize().x), MathHelper::RandInt(0, map.GetSize().y));
        }
        SetUpperLeftCorner(sf::Vector2f(curPos.x*16+MathHelper::RandInt(0, 9), curPos.y*16+16-GetGlobalHitbox().height));
        sf::Vector2f rc = MathHelper::GetCenter(GetGlobalHitbox());

        if(level.GetSpawner().IsCollided(*this)) {  //in pipe?
            correctPos = false;
        }
        for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {  //in ennemy?
            if(GetGlobalHitbox().intersects(eManager.GetEnnemy(i)->GetGlobalHitbox())) {
                correctPos = false;
                break;
            }
        }
        if(abs(rc.x-MathHelper::GetCenter(character.GetGlobalHitbox()).x) < 42) {   //near to player?
            correctPos = false;
        }
    }

    _outTime = MathHelper::RandFloat(3000, 8000);
    _outTimer.restart();
    return true;
}

void RockWorm::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager) {
    AnimationTable& anims(GetAnims());
    if(anims.GetAnimationName() == "spawn" && anims.GetAnimation().IsFinished()) {
        anims.SetAnimation("idle");
    }
    if(anims.GetAnimationName() == "despawn" && anims.GetAnimation().IsFinished()) {
        AutoSpawn(ip, level, eManager, character);
        anims.SetAnimation("spawn");
    } else if(anims.GetAnimationName() != "despawn") {
        if(_outTimer.getElapsedTime().asMilliseconds() >= _outTime) {
            anims.SetAnimation("despawn");
        }
    }

    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    if(c.x < cc.x) {
        GoRight(eTime);
    } else if(c.x > cc.x) {
        GoLeft(eTime);
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager);
}
