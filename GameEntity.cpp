#include "GameEntity.h"
#include "Level.h"
#include "Map.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "Particle.h"
#include "DamageParticle.h"

GameEntity::GameEntity(IP& ip, string name, sf::IntRect hitbox, int hp) : MovingSprite(ip, name, hitbox, true) {
    _jumpPower = 0.7;
    _speed = 0.003;
    _weight = 0.3;
    _alive = true;
    _hpMax = hp;
    _hp = _hpMax;
    _dir = true;
    _pushable = true;
}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager, ParticleManager& pManager) {
    //SetVel(sf::Vector2f(GetVel().x / 1.2f, GetVel().y));
    Accelerate(sf::Vector2f(0, 0.003), elapsedTime);
    Accelerate(sf::Vector2f(-0.008*GetVel().x, 0), elapsedTime);

    for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
        Ennemy* e = eManager.GetEnnemy(i);
        if((GameEntity*)(e) == this) {
            continue;
        }
        //if(MathHelper::ABS(e.getPosition().x-getPosition().x) > 42)
        Collide((GameEntity*)e, elapsedTime);
    }

    MovingSprite::Update(ip, elapsedTime, level);
}

void GameEntity::Update(IP& ip, float elapsedTime) {
    MovingSprite::Update(ip, elapsedTime);
}

void GameEntity::Collide(GameEntity* other, float elapsedTime) {
    sf::Vector2f delta = -GetVel()*elapsedTime;
    float vecLength = MathHelper::GetVecLength(delta);
    sf::Vector2f dir = MathHelper::Normalize(delta);
    //cout << vecLength << endl;
    for(float i=0 ; i<vecLength ; i++) {
        sf::Vector2f curPos = GetUpperLeftPos() - delta-(i*dir);
        sf::FloatRect r = sf::FloatRect(GetHitbox().left+curPos.x, GetHitbox().top+curPos.y, GetHitbox().width, GetHitbox().height);
        sf::FloatRect r2 = other->GetGlobalHitbox();

        if(!r.intersects(r2)) {
            continue;
        }

        sf::Vector2f c = MathHelper::GetCenter(r);
        sf::Vector2f c2 = MathHelper::GetCenter(r2);
        sf::Vector2f dist = MathHelper::ABS(sf::Vector2f(c-c2));
        float rx = (r.width/2.f + r2.width/2.f - dist.x) / (r.width/2.f + r2.width/2.f);
        float dx = rx*MathHelper::SGN(sf::Vector2f(c-c2).x);
        dx = max(-0.5f, min(dx, 0.5f));

        if(IsPushable()) SetVel(GetVel() + sf::Vector2f(dx, 0)*other->GetWeight());
        if(other->IsPushable()) other->SetVel(other->GetVel() - sf::Vector2f(dx, 0)*GetWeight());

        return;
    }
}

void GameEntity::GoLeft(float eTime) {
    float acc = -_speed - 0.007*GetVel().x;
    if(acc < 0) {
        Accelerate(sf::Vector2f(acc, 0), eTime);
    }
    if(_dir == true) {
        ChangeDir();
    }
}

void GameEntity::GoRight(float eTime) {
    float acc = _speed - 0.007*GetVel().x;
    if(acc > 0) {
        Accelerate(sf::Vector2f(acc, 0), eTime);
    }
    if(_dir == false) {
        ChangeDir();
    }
}

void GameEntity::ChangeDir() {
    _dir = _dir == false;
    if(_dir) {
        setScale(1, 1);
    } else {
        setScale(-1, 1);
    }
    sf::Vector2f frameSize(GetAnims().GetAnimation().GetRect().width, GetAnims().GetAnimation().GetRect().height);
    SetHitbox(sf::IntRect(frameSize.x-GetHitbox().left-GetHitbox().width, frameSize.y-GetHitbox().top-GetHitbox().height, GetHitbox().width, GetHitbox().height));
}

void GameEntity::Jump(Level& level) {
    if(!level.GetSpawner().IsOnGround(*this) && !level.GetMap().IsOnTileType(*this, Map::WALL)) {
        return;
    }
    SetVel(sf::Vector2f(GetVel().x, -_jumpPower));
}

void GameEntity::Damage(int dmg, IP& ip, ParticleManager& pManager) {
    _hp -= dmg;
    if(_hp <= 0) {
        _alive = false;
    }

    pManager.AddParticle(new DamageParticle(ip,
                                            dmg,
                                            sf::Vector2f(getPosition().x, getPosition().y-20),
                                            /*sf::Vector2f(0, -0.1)*/MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(250, 290))) * MathHelper::RandFloat(0.2, 0.4),
                                            sf::Vector2f(1, 1),
                                            sf::Vector2f(1, 1),
                                            true,
                                            true));
}

void GameEntity::Hit(GameEntity *other, IP& ip, ParticleManager& pManager) {
    other->Damage(MathHelper::RandInt(2, 5), ip, pManager);
    sf::Vector2f c(MathHelper::GetCenter(GetGlobalHitbox()));
    sf::Vector2f oc(MathHelper::GetCenter(other->GetGlobalHitbox()));
    sf::Vector2f dir = MathHelper::Normalize(sf::Vector2f(oc.x-c.x, 0));
    other->SetVel(other->GetVel() + sf::Vector2f(dir.x, 0)*0.07f/other->GetWeight());

    for(int i=0 ; i<5 ; i++) {
        Particle *p = new Particle(ip, "blood1",
                                   sf::Vector2f(other->GetGlobalHitbox().left+other->GetGlobalHitbox().width/2.f, other->GetGlobalHitbox().top+MathHelper::RandFloat(other->GetGlobalHitbox().height/2.f, other->GetGlobalHitbox().height/4.f)),
                                   (dir - sf::Vector2f(0, MathHelper::RandFloat(0.4, 1))) * MathHelper::RandFloat(0.1, 0.2),
                                   0,
                                   350,
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   255,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(3, 2, 1, 2));
        p->GetAnims().AddAnimation("base", new Animation(7, 50, sf::Vector2i(0, 0), sf::Vector2i(6, 6), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }

    for(int i=0 ; i<10 ; i++) {
        Particle *p = new Particle(ip, "blood0",
                                   sf::Vector2f(other->GetGlobalHitbox().left+other->GetGlobalHitbox().width/2.f, other->GetGlobalHitbox().top+MathHelper::RandFloat(other->GetGlobalHitbox().height/2.f, other->GetGlobalHitbox().height/4.f)),
                                   (dir - sf::Vector2f(0, MathHelper::RandFloat(0.6, 1.2))) * MathHelper::RandFloat(0.1, 0.2),
                                   0,
                                   300,
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   255,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(2, 1, 1, 2));
        p->GetAnims().AddAnimation("base", new Animation(6, 50, sf::Vector2i(0, 0), sf::Vector2i(4, 4), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
}

void GameEntity::SetJumpPower(float p) {
    _jumpPower = p;
}

void GameEntity::SetSpeed(float s) {
    _speed = s;
}

void GameEntity::SetWeight(float w) {
    _weight = w;
}

void GameEntity::SetPushable(bool p) {
    _pushable = p;
}

float GameEntity::GetWeight() {
    return _weight;
}

bool GameEntity::IsAlive() {
    return _alive;
}

int GameEntity::GetHp() const {
    return _hp;
}

int GameEntity::GetHpMax() const {
    return _hpMax;
}

bool GameEntity::GetDir() {
    return _dir;
}

bool GameEntity::IsPushable() {
    return _pushable;
}
