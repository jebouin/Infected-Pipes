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
#include "SandBullet.h"

RockWorm::RockWorm(IP& ip, Level& level) : Ennemy(ip, "rockWorm", sf::IntRect(2, 2, 8, 28), 7, 2, 2, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", Animation(4, 200, sf::Vector2i(0, 0), sf::Vector2i(12, 30), true));
    t.AddAnimation("static", Animation(1, 80, sf::Vector2i(0, 30), sf::Vector2i(12, 30), false));
    t.AddAnimation("attack", Animation(7, 60, sf::Vector2i(0, 30), sf::Vector2i(12, 30), false));
    t.SetAnimation("static");
    SetPushable(false);
    SetFlying(true);
    SetPhysics(false);
    SetSpeed(0);
    _curState = SDOWN;
    _stateTime = 300;
    _attacked = false;
}

RockWorm::~RockWorm() {

}

bool RockWorm::AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character) {
    Map& map(level.GetMap());
    vector<sf::Vector2i> correctPos;
    //list all correct positions   .
    //                             P
    //                             #
    //                             #
    for(int i=0 ; i<map.GetSize().x-1 ; i++) {
        for(int j=0 ; j<map.GetSize().y ; j++) {
            sf::Vector2i curPos(i, j);
            if(map.GetTileType(curPos+UP, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos+DOWN, Map::FRONT) == Map::WALL &&
               map.GetTileType(curPos+2*DOWN, Map::FRONT) == Map::WALL) {
                correctPos.push_back(curPos);
            }
        }
    }
    if(correctPos.size() == 0) {
        return false; //no correct pos...
    }
    //keep the pos with a correct distance from player
    static const float minL = 48;
    static const float maxL = 160;
    for(int i=0 ; i<correctPos.size() ; i++) {
        sf::Vector2i curPos(correctPos[i]);
        sf::Vector2f relPos(sf::Vector2f(curPos*16) + sf::Vector2f(8, 16));
        float dist(MathHelper::GetVecLength(relPos-character.getPosition()));
        if(dist > maxL || dist < minL) {
            correctPos.erase(correctPos.begin() + i);
            i--;
        }
    }
    //remove positions colliding with a pipe
    for(int i=0 ; i<correctPos.size() ; i++) {
        sf::Vector2i curPos(correctPos[i]);
        if(level.GetSpawner().IsCollided(sf::FloatRect(curPos.x*16, curPos.y*16-16, 16, 32))) {
            correctPos.erase(correctPos.begin() + i);
            i--;
        }
    }
    //and pick a random one
    sf::Vector2i finPos(correctPos[rand()%correctPos.size()]);
    float xOff(MathHelper::RandFloat(-2, 2));
    _upPos = sf::Vector2f(sf::Vector2f(finPos*16) + sf::Vector2f(8+xOff, 3));
    setPosition(_upPos + sf::Vector2f(0, 30));
    _downPos = getPosition();
    SetHitbox(sf::IntRect(0, 0, 0, 0));
    _attacked = false;
    return true;
}

void RockWorm::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& anims(GetAnims());
    sf::Vector2f charPos(character.getPosition());

    if(charPos.x > getPosition().x) {
        if(!GetDir()) {
            ChangeDir();
        }
    } else {
        if(GetDir()) {
            ChangeDir();
        }
    }

    switch(_curState) {
    case SGOINGUP:
        SetVel(sf::Vector2f(0, -.1f));
        if(getPosition().y < _upPos.y) {
            setPosition(sf::Vector2f(getPosition().x, _upPos.y));
            SetVel(sf::Vector2f(0, 0));
            _curState = SUP;
            _stateTimer.restart();
            _stateTime = 1000;
            anims.SetAnimation("idle");
        }
        break;
    case SGOINGDOWN:
        SetVel(sf::Vector2f(0, .1f));
        if(getPosition().y > _downPos.y) {
            setPosition(sf::Vector2f(getPosition().x, _downPos.y));
            SetVel(sf::Vector2f(0, 0));
            _curState = SDOWN;
            _stateTimer.restart();
            _stateTime = 1000;
            AutoSpawn(ip, level, eManager, character);
        }
        break;
    case SUP:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            if(_attacked) {
                _curState = SGOINGDOWN;
            } else {
                anims.SetAnimation("attack");
                _curState = SATTACKING;
                _attacked = false;
            }
            _stateTimer.restart();
        }
        break;
    case SDOWN:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            _stateTimer.restart();
            _curState = SGOINGUP;
            SetHitbox(sf::IntRect(2, 2, 8, 28));
        }
        break;
    case SATTACKING:
        if(!_attacked && anims.GetAnimation().GetCurFrame() == 1) {
            SandBullet *b = new SandBullet(ip, getPosition()+sf::Vector2f(0, -5), sf::Vector2f((GetDir() ? .15 : -.15), 0), true);
            b->setScale(GetDir() ? 1 : -1, 1);
            bManager.AddBullet(b);
            _attacked = true;
        }
        if(anims.GetAnimation().IsFinished()) {
            _curState = SUP;
            anims.SetAnimation("idle");
        }
        break;
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void RockWorm::Draw(IP& ip) {
    if(_curState != SDOWN) {
        Ennemy::Draw(ip);
    }
}

void RockWorm::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    /*for(int i=0 ; i<20 ; i++) {
        Particle *p = new Particle(ip, "rockWormBlood",
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.02, .05),
                                   0,
                                   480,
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(2, 2, 2, 1), false);
        p->GetAnims().AddAnimation("base", Animation(6, 80, sf::Vector2i(0, 0), sf::Vector2i(6, 5), false));
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
                                      sf::IntRect(0, 0, 6, 5), false));*/
}
