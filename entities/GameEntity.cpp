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
#include "WaterField.h"
#include "IP.h"
#include "Renderer.h"

GameEntity::GameEntity(IP& ip, std::string name, sf::IntRect hitbox, int hp) : MovingSprite(ip, name, hitbox, true) {
    _jumpPower = 0.69;
    _speed = 0.003;
    _weight = 0.3;
    _alive = true;
    _hpMax = hp;
    _hp = _hpMax;
    _dir = true;
    _pushable = true;
    _flying = false;
    _invincible = false;
    _autoDir = true;
    _inWater = false;
    _friction = .008;
    _havePhysics = true;
    _lastTimeHit = -10000;
    _waterFriction = 1;
    _hitShaderAmp = 1.f;

    if(!_hitShader.loadFromFile("shaders/hit.frag", sf::Shader::Fragment)) {
        cout << "Could not load hit shader..." << endl;
    }
}

GameEntity::~GameEntity() {

}

void GameEntity::Update(IP& ip, float elapsedTime, Level& level, EntityManager& eManager, ParticleManager& pManager) {
    _inWater = IsInWater(level);
    bool onGround = (level.GetSpawner().IsOnGround(*this) || level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM));

    _hitShader.setParameter("texture", sf::Shader::CurrentTexture);
    _hitShader.setParameter("time", _hitTimer.getElapsedTime().asMilliseconds());
    _hitShader.setParameter("lastTimeHit", _lastTimeHit);
    _hitShader.setParameter("amp", _hitShaderAmp);

    if(!_havePhysics) {
        MovingSprite::Update(ip, elapsedTime);
        return;
    }

    if(!_flying) {
        if(!_inWater) {
            Accelerate(sf::Vector2f(0, 0.003), elapsedTime);
        } else {
            Accelerate(sf::Vector2f(0, 0.002), elapsedTime);
        }
    } else {
        Accelerate(sf::Vector2f(0, -0.008*GetVel().y), elapsedTime);
    }
    //ice friction here
    Accelerate(sf::Vector2f(-_friction*GetVel().x, 0), elapsedTime);

    if(_inWater && GetCollidesWithWater()) {
        Accelerate(sf::Vector2f(-0.02*GetVel().x*_waterFriction, -0.02*GetVel().y*_waterFriction), elapsedTime);
    }

    //collides with enemies
    for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
        Ennemy* e = eManager.GetEnnemy(i);
        if((GameEntity*)(e) == this) {
            continue;
        }
        //if(MathHelper::ABS(e.getPosition().x-getPosition().x) > 42)
        Collide((GameEntity*)e, elapsedTime);
    }
    //and with passive entities
    for(int i=0 ; i<level.GetNbPassiveEntities() ; i++) {
        GameEntity* e = level.GetPassiveEntity(i);
        if(e == this) {
            continue;
        }
        Collide(e, elapsedTime);
    }

    MovingSprite::Update(ip, elapsedTime, level, pManager);
}

void GameEntity::Update(IP& ip, float elapsedTime) {
    MovingSprite::Update(ip, elapsedTime);
}

void GameEntity::Draw(IP& ip) {
    MovingSprite::Draw(ip, &_hitShader);
}

void GameEntity::Collide(GameEntity* other, float elapsedTime) {
    /*if(!_havePhysics || !other->HasPhysics()) {
        return;
    }*/
    sf::Vector2f delta = -GetVel()*elapsedTime;
    float vecLength = MathHelper::GetVecLength(delta);
    sf::Vector2f dir = MathHelper::Normalize(delta);
    //cout << vecLength << endl;
    for(float i=0 ; i<vecLength ; i++) {
        sf::Vector2f curPos = GetGlobalUpperLeftPos() - delta-(i*dir);
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
        dx = std::max(-0.5f, std::min(dx, 0.5f));

        if(IsPushable() && HasPhysics()) SetVel(GetVel() + sf::Vector2f(dx, 0)*other->GetWeight());
        if(other->IsPushable() && other->HasPhysics()) other->SetVel(other->GetVel() - sf::Vector2f(dx, 0)*GetWeight());

        return;
    }
}

void GameEntity::GoLeft(float eTime) {
    float acc = -_speed - 0.007*GetVel().x;
    if(acc < 0) {
        Accelerate(sf::Vector2f(acc, 0), eTime);
    }
    if(_dir == true && _autoDir) {
        ChangeDir();
    }
}

void GameEntity::GoRight(float eTime) {
    float acc = _speed - 0.007*GetVel().x;
    if(acc > 0) {
        Accelerate(sf::Vector2f(acc, 0), eTime);
    }
    if(_dir == false && _autoDir) {
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
    SetHitbox(sf::IntRect(frameSize.x-GetHitbox().left-GetHitbox().width+1, GetHitbox().top, GetHitbox().width, GetHitbox().height));
}

void GameEntity::PlatformDrop(Level& level) {
    Map& m(level.GetMap());
    if(m.IsOnTileType(*this, Map::WALL)) {
        return;
    }
    if(!m.IsOnTileType(*this, Map::PLATFORM)) {
        return;
    }
    setPosition(sf::Vector2f(getPosition().x, getPosition().y+4));
}

bool GameEntity::Jump(Level& level) {
    if(!level.GetSpawner().IsOnGround(*this) && !level.GetMap().IsOnTileType(*this, Map::WALL) && !level.GetMap().IsOnTileType(*this, Map::PLATFORM) && !_inWater) {
        return false;
    }
    if(GetVel().y < 0) {
        return false;
    }
    if(_inWater) {
        SetVel(sf::Vector2f(GetVel().x, -_jumpPower*1.3));
    } else {
        SetVel(sf::Vector2f(GetVel().x, -_jumpPower));
    }
    return true;
}

void GameEntity::Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level) {
    if(_invincible) {
        return;
    }

    _hp -= dmg;
    if(_hp <= 0) {
        Die(ip, pManager, eManager, level);
        _hp = 0;
    }

    pManager.AddParticle(new DamageParticle(ip,
                                            dmg,
                                            sf::Vector2f(getPosition().x, getPosition().y-20),
                                            MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(250, 290))) * MathHelper::RandFloat(0.2, 0.4),
                                            sf::Vector2f(1, 1),
                                            sf::Vector2f(1, 1),
                                            color,
                                            true,
                                            true));
    ResetHitShader();
}

void GameEntity::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    _alive = false;
}

void GameEntity::Hit(GameEntity *other, IP& ip, ParticleManager& pManager, sf::Color color, int damage, EntityManager& eManager, Level& level) {
    other->Damage(damage, ip, pManager, color, other->getPosition(), MathHelper::Normalize(other->getPosition() - getPosition())*0.1f, eManager, level);
    sf::Vector2f c(MathHelper::GetCenter(GetGlobalHitbox()));
    sf::Vector2f oc(MathHelper::GetCenter(other->GetGlobalHitbox()));
    sf::Vector2f dir = MathHelper::Normalize(sf::Vector2f(oc.x-c.x, 0));
    other->SetVel(other->GetVel() + sf::Vector2f(dir.x, 0)*0.07f/other->GetWeight());
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

void GameEntity::SetFlying(bool f) {
    _flying = f;
}

void GameEntity::SetHP(int hp) {
    _hp = std::max(std::min(hp, _hpMax), 0);
}

void GameEntity::SetHPMax(int hpMax) {
    _hpMax = std::max(hpMax, 0);
}

void GameEntity::SetAlive(bool a) {
    _alive = a;
}

void GameEntity::SetInvincible(bool i) {
    _invincible = i;
}

void GameEntity::SetAutoDir(bool a) {
    _autoDir = a;
}

void GameEntity::SetFriction(float friction) {
    _friction = friction;
}

void GameEntity::SetPhysics(bool p) {
    _havePhysics = p;
}

float GameEntity::GetSpeed() {
    return _speed;
}

float GameEntity::GetWeight() {
    return _weight;
}

bool GameEntity::IsAlive() {
    return _alive;
}

int GameEntity::GetHP() const {
    return _hp;
}

int GameEntity::GetHPMax() const {
    return _hpMax;
}

bool GameEntity::GetDir() {
    return _dir;
}

bool GameEntity::IsPushable() {
    return _pushable;
}

bool GameEntity::IsInvincible() {
    return _invincible;
}

bool GameEntity::HasPhysics() const {
    return _havePhysics;
}

void GameEntity::SetWaterFriction(float f) {
    _waterFriction = f;
}

void GameEntity::ResetHitShader() {
    _lastTimeHit = _hitTimer.getElapsedTime().asMilliseconds();
}
