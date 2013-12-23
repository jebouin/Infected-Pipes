#include "Fist.h"
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
#include "Bullet.h"

Fist::Fist(IP& ip, Level& level)
    : Ennemy(ip, "fist", sf::IntRect(4, 2, 17, 36), 200, 30, 40, level) {
    _stateTime = 300;
    _curState = SDOWN;
    SetPushable(false);
    SetFlying(true);
    SetPhysics(false);
}

Fist::~Fist() {

}

bool Fist::AutoSpawn(IP& ip, Level& level, EntityManager& eManager, Character& character) {
    Map& map(level.GetMap());
    vector<sf::Vector2i> correctPos;
    //list all correct positions   ..
    //                             P.
    //                             ##
    //                             ##
    for(int i=0 ; i<map.GetSize().x-1 ; i++) {
        for(int j=0 ; j<map.GetSize().y ; j++) {
            sf::Vector2i curPos(i, j);
            if(map.GetTileType(curPos+UP, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos+RIGHT+UP, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos+RIGHT, Map::FRONT) == Map::VOID &&
               map.GetTileType(curPos+DOWN, Map::FRONT) == Map::WALL &&
               map.GetTileType(curPos+DOWN+RIGHT, Map::FRONT) == Map::WALL &&
               map.GetTileType(curPos+2*DOWN, Map::FRONT) == Map::WALL &&
               map.GetTileType(curPos+2*DOWN+RIGHT, Map::FRONT) == Map::WALL) {
                correctPos.push_back(curPos);
            }
        }
    }
    //okay, now lets remove pos where there is another enemy
    for(int i=0 ; i<correctPos.size() ; i++) {
        sf::Vector2i curPos(correctPos[i]);
        sf::FloatRect curRect(curPos.x*16, curPos.y*16, 32, 32);
        for(int j=0 ; j<eManager.GetNbEnnemies() ; j++) {
            Ennemy* e(eManager.GetEnnemy(j));
            sf::FloatRect eRect(e->GetGlobalHitbox());
            if(eRect.intersects(curRect)) {
                correctPos.erase(correctPos.begin() + i);
                i--;
                break;
            }
        }
    }
    if(correctPos.size() == 0) {
        return false; //no correct pos yet...
    }
    //now we keep the closest pos to player
    float bestDist = 42000000;
    int bestId = 0;
    for(int i=0 ; i<correctPos.size() ; i++) {
        sf::Vector2i curPos(correctPos[i]);
        sf::Vector2f deltaPos(character.getPosition() - sf::Vector2f((curPos+DOWN+RIGHT)*16));
        float curDist= MathHelper::GetVecLength(deltaPos);
        if(curDist < bestDist) {
            bestDist = curDist;
            bestId = i;
        }
    }
    sf::Vector2i bestPos = correctPos[bestId];
    _upPos = sf::Vector2f((bestPos+RIGHT)*16);
    setPosition(_upPos + sf::Vector2f(0, 32));
    _downPos = getPosition();
    SetHitbox(sf::IntRect(0, 0, 0, 0));
    return true;
}

void Fist::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
    //MovingSprite::Update(ip, eTime);

    switch(_curState) {
    case SGOINGUP:
        SetVel(sf::Vector2f(0, -1.f));
        if(getPosition().y < _upPos.y) {
            setPosition(sf::Vector2f(getPosition().x, _upPos.y));
            SetVel(sf::Vector2f(0, 0));
            _curState = SUP;
            _stateTimer.restart();
            _stateTime = 1000;
        }
        if(character.GetGlobalHitbox().intersects(GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() >= 200) {
            _attackTimer.restart();
            character.Damage(32, ip, pManager, sf::Color(255, 0, 0), sf::Vector2f(character.getPosition().x, getGlobalBounds().top), MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-110, -70)))*-1.1f, eManager, level);
            character.SetVel(sf::Vector2f(character.GetVel().x, -1.f));
        }
        break;
    case SGOINGDOWN:
        SetVel(sf::Vector2f(0, .5f));
        if(getPosition().y > _downPos.y) {
            setPosition(sf::Vector2f(getPosition().x, _downPos.y));
            SetVel(sf::Vector2f(0, 0));
            _curState = SDOWN;
            _stateTimer.restart();
            _stateTime = 1000;
            AutoSpawn(ip, level, eManager, character);
        }
        break;
    case SDOWN:
        if(_particleTimer.getElapsedTime().asMilliseconds() >= 100) {
            pManager.AddParticle(new Particle(ip, "snowSmokeParticle",
                                              sf::Vector2f(getPosition().x + MathHelper::RandFloat(-8, 8), getPosition().y-17),
                                              sf::Vector2f(0., 0.),
                                              MathHelper::RandFloat(-.5, .5),
                                              MathHelper::RandFloat(200, 400),
                                              sf::Vector2f(.5, .5),
                                              sf::Vector2f(2., 2.),
                                              128,
                                              0,
                                              false,
                                              false,
                                              false,
                                              sf::IntRect(2, 2, 3, 3), false));
        }
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            _stateTimer.restart();
            _curState = SGOINGUP;
            SetHitbox(sf::IntRect(4, 2, 17, 36));
        }
        break;
    case SUP:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            _stateTimer.restart();
            _curState = SGOINGDOWN;
        }
        break;
    }
}

void Fist::Draw(IP& ip) {
    if(_curState != SDOWN) {
        Ennemy::Draw(ip);
    }
}

void Fist::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);

    for(int i=0 ; i<8 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 6, 5) : sf::IntRect(1, 1, 8, 8));
        Particle *p = new Particle(ip, (type == 0 ? "snowRockParticle" : "snowRockParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.2, .5),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(800, 1200),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }
    for(int i=0 ; i<4 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 7, 8) : sf::IntRect(1, 1, 7, 10));
        Particle *p = new Particle(ip, (type == 0 ? "fingerParticle" : "fingerParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.4, .6),
                                   MathHelper::RandFloat(-.3, .3),
                                   MathHelper::RandFloat(1000, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }
}
