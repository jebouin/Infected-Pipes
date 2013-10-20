#include "RockWorm.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "RockWorm.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"
#include "RockBullet.h"

RockWorm::RockWorm(IP& ip, Level& level) : Ennemy(ip, "rockWorm", sf::IntRect(1, 0, 7, 19), 7, 2, 2, level) {
    _littleHitBox = sf::IntRect(1, 0, 7, 19);
    _bigHitBox = sf::IntRect(3, 0, 9, 20);

    AnimationTable& t(GetAnims());
    t.AddAnimation("spawn", new Animation(4, 60, sf::Vector2i(0, 0), sf::Vector2i(9, 20), false));
    t.AddAnimation("idle", new Animation(4, 200, sf::Vector2i(0, 20), sf::Vector2i(9, 20), true));
    t.AddAnimation("attack", new Animation(4, 80, sf::Vector2i(0, 40), sf::Vector2i(15, 20), false));
    t.AddAnimation("despawn", new Animation(4, 60, sf::Vector2i(0, 60), sf::Vector2i(9, 20), false));
    t.SetAnimation("spawn");
    SetSpeed(0);
    SetPushable(false);
    _outTime = MathHelper::RandFloat(3000, 8000);
    _shot = false;
}

RockWorm::~RockWorm() {

}

bool RockWorm::AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character) {
    _outTime = MathHelper::RandFloat(3000, 8000);
    _outTimer.restart();

    Map& map(level.GetMap());
    bool possible = false;
    for(int i=0 ; i<map.GetSize().x ; i++) {
        for(int j=0 ; j<map.GetSize().y ; j++) {
            if(map.GetTileType(sf::Vector2i(i, j), Map::FRONT) == Map::VOID && map.GetTileType(sf::Vector2i(i, j+1), Map::FRONT) == Map::WALL) {
                possible = true;
            }
        }
    }
    if(!possible) {
        return false;
    }

    bool correctPos = false;
    int tries = 0;
    while(!correctPos) {
        tries++;
        correctPos = true;
        sf::Vector2i curPos(-1, -1);
        while(!(map.GetTileType(curPos, Map::FRONT) == Map::VOID && map.GetTileType(curPos + sf::Vector2i(0, 1), Map::FRONT) == Map::WALL)) {
            curPos = sf::Vector2i(MathHelper::RandInt(0, map.GetSize().x), MathHelper::RandInt(0, map.GetSize().y));
        }
        SetUpperLeftCorner(sf::Vector2f(curPos.x*16+MathHelper::RandInt(1, 8), curPos.y*16+16-GetGlobalHitbox().height));
        sf::Vector2f rc = MathHelper::GetCenter(GetGlobalHitbox());

        if(level.GetSpawner().IsCollided(*this)) {  //in pipe?
            correctPos = false;
        }
        for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {  //in ennemy?
            if(eManager.GetEnnemy(i) == this) {
                continue;
            }
            if(GetGlobalHitbox().intersects(eManager.GetEnnemy(i)->GetGlobalHitbox())) {
                correctPos = false;
                break;
            }
        }
        float distFromCharacter = MathHelper::GetVecLength(rc-MathHelper::GetCenter(character.GetGlobalHitbox()));
        if(distFromCharacter < 42 || distFromCharacter > 300) {   //near to player?
            correctPos = false;
        }

        if(tries > 1000) {
            return false;
        }
    }
    return true;
}

void RockWorm::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& anims(GetAnims());
    if(anims.GetAnimationName() == "spawn" && anims.GetAnimation().IsFinished()) {
        anims.SetAnimation("idle");
    }
    if(anims.GetAnimationName() == "despawn" && anims.GetAnimation().IsFinished()) {
        AutoSpawn(ip, level, eManager, character);
        anims.SetAnimation("spawn");
    } else if(anims.GetAnimationName() == "idle") {
        if(_outTimer.getElapsedTime().asMilliseconds() >= _outTime) {
            anims.SetAnimation("despawn");
        }
    }

    if(anims.GetAnimationName() == "idle") { //start attack
        if(_attackTimer.getElapsedTime().asMilliseconds() > 1200) {
            _attackTimer.restart();
            SetHitbox(_bigHitBox);
            move(sf::Vector2f(GetDir() ? -3 : 3, 0));
            anims.SetAnimation("attack");
        }
    }

    if(anims.GetAnimationName() == "attack") { //attack
        if(anims.GetAnimation("attack").GetCurFrame() == 3 && !_shot) { //frame 3, shoot the rock
            bManager.AddBullet(new RockBullet(ip,
                                              MathHelper::GetCenter(GetGlobalHitbox()) + sf::Vector2f(0, -6),
                                              MathHelper::Ang2Vec(MathHelper::Deg2Rad((GetDir() ? -30 : 210) + MathHelper::RandFloat(-10, 10)))*MathHelper::RandFloat(0.2, 0.3),
                                              true));
            _shot = true;
        }

        if(anims.GetAnimation().IsFinished()) { //finished
            _attackTimer.restart();
            anims.SetAnimation("idle");
            SetHitbox(_littleHitBox);
            move(sf::Vector2f(GetDir() ? 3 : -3, 0));
            _shot = false;
        }
    }

    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    if(anims.GetAnimationName() != "attack") {
        if(abs(c.x - cc.x) > 10) {
            if(c.x < cc.x) {
                GoRight(eTime);
            } else if(c.x > cc.x) {
                GoLeft(eTime);
            }
        }
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void RockWorm::Die(IP& ip, ParticleManager& pManager) {
    GameEntity::Die(ip, pManager);
    for(int i=0 ; i<20 ; i++) {
        Particle *p = new Particle(ip, "rockWormBlood",
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.02, .05),
                                   0,
                                   480,
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(2, 2, 2, 1));
        p->GetAnims().AddAnimation("base", new Animation(6, 80, sf::Vector2i(0, 0), sf::Vector2i(6, 5), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
    pManager.AddParticle(new Particle(ip, "rockWormHead",
                                      getPosition()+sf::Vector2f(3, 2),
                                      sf::Vector2f(0., -MathHelper::RandFloat(.3, .6)),
                                      MathHelper::RandFloat(-.2, .2),
                                      MathHelper::RandFloat(1000, 2000),
                                      sf::Vector2f(1., 1.),
                                      sf::Vector2f(2., 2.),
                                      255,
                                      0,
                                      true,
                                      true,
                                      false,
                                      sf::IntRect(0, 0, 6, 5)));
}
