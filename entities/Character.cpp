#include "Character.h"
#include "IP.h"
#include "Animation.h"
#include "Ennemy.h"
#include "AnimationTable.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Level.h"
#include "Spawner.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "Weapon.h"
#include "ShotGun.h"
#include "MachineGun.h"
#include "Rifle.h"
#include "Particle.h"
#include "ResourceLoader.h"
#include "GUI.h"
#include "ElectricGun.h"
#include "GroundAttackBullet.h"
#include "Map.h"
#include "HealingFly.h"
#include "HealingParticle.h"

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(4, 3, 7, 26), 20) {
    _arms[EMPTY] = Arm {sf::IntRect(0, 0, 6, 9), sf::Vector2f(2, 1), sf::Vector2f(5, 6), 0};
    _arms[SHOTGUN] = Arm{sf::IntRect(0, 35, 21, 10), sf::Vector2f(5, 1), sf::Vector2f(6, 4), -90};
    _arms[MACHINEGUN] = Arm{sf::IntRect(0, 44, 23, 10), sf::Vector2f(8, 1), sf::Vector2f(8, 2), -90};
    _arms[RIFLE] = Arm{sf::IntRect(0, 54, 28, 9), sf::Vector2f(8, 1), sf::Vector2f(10, 3), -90};
    _arms[ELECTRICGUN] = Arm{sf::IntRect(0, 63, 20, 9), sf::Vector2f(7, 1), sf::Vector2f(12, 4), -90};

    SetWeight(0.5f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", Animation(8, 100, sf::Vector2i(0, 0), sf::Vector2i(15, 31), true));
    t.AddAnimation("idle", Animation(1, 50, sf::Vector2i(0, 31), sf::Vector2i(15, 31), false));
    t.SetAnimation("walk");
    _enteringPipe = false;
    _leavingPipe = false;
    _canContinueJump = false;
    _prevVelY = 0;

    _level = 0;
    _xp = 0;
    _nextXP = 10;
    _baseHP = 20;
    _hpMult = 1.;
    _regen = 0;
    _baseSpeed = 0.0026;
    SetSpeed(_baseSpeed);
    _baseJump = .69;
    SetJumpPower(_baseJump);
    _groundAttackLevel = 0;

    _weapon = new MachineGun(ip, (const GameEntity&)*this, sf::Vector2f(0, 0));

    _arm.setTexture(ResourceLoader::GetTexture("arms"));
    LoadArm(MACHINEGUN);

    SetAutoDir(false);
    SetCollisionPrecision(.05);
}

Character::~Character() {
    delete _weapon;
    _weapon = 0;
    for(int i=0 ; i<_flies.size() ; i++) {
        delete _flies[i];
        _flies[i] = 0;
    }
}

void Character::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager, Player& player) {
    sf::Vector2f mpos = MathHelper::GetMousePos(ip);
    AnimationTable& t(GetAnims());

    if(_enteringPipe) {
        _arm.setRotation(_arms[_curArmType]._onPipeRotation + (GetDir() ? 0 : 180));
        SetVel(sf::Vector2f(0, 0.1));
        MovingSprite::Update(ip, eTime);
        if(_enterTimer.getElapsedTime().asMilliseconds() > 500) {
            _enteringPipe = false;
            level.NextLevel(ip, eManager, bManager, player, pManager);
            _leavingPipe = true;
            _enterTimer.restart();
        }
    } else if (_leavingPipe) {
        _arm.setRotation(_arms[_curArmType]._onPipeRotation + (GetDir() ? 0 : 180));
        SetVel(sf::Vector2f(0, 0.1));
        MovingSprite::Update(ip, eTime);
        if(!level.GetSpawner().IsCollided(*this)) {
            _enterTimer.restart();
            _leavingPipe = false;
        }
    } else {
        GameEntity::Update(ip, eTime, level, eManager, pManager);
        float r = MathHelper::Rad2Deg(MathHelper::Vec2Ang(mpos-_arm.getPosition()));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _weapon->Use(ip, bManager, r, eManager, level, pManager);
        }
        if(!GetDir()) {
            _arm.setScale(-1, 1);
            r -= 180;
        } else {
            _arm.setScale(1, 1);
        }
        _arm.setRotation(r);
    }

    if(IsInLava(level) && GetHP() > 0) {
        Damage(GetHP(), ip, pManager, sf::Color(255, 0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, -.1), eManager, level);
    }

    sf::Vector2f framed(0, 0);
    if(t.GetAnimationName() == "idle") {
        framed = sf::Vector2f(0, 0);
    } else if(t.GetAnimationName() == "walk") {
        int a = t.GetAnimation().GetCurFrame()%4;
        framed.y = -((a == 1 ? 2 : (a==2 ? 1 : 0)));
    }
    if(GetDir()) {
        if(mpos.x < _arm.getPosition().x) {
            ChangeDir();
        }
        _arm.setPosition(GetGlobalUpperLeftPos() + sf::Vector2f(4, 12) + framed);
    } else {
        if(mpos.x > _arm.getPosition().x) {
            ChangeDir();
        }
        _arm.setPosition(GetGlobalUpperLeftPos() + sf::Vector2f(getLocalBounds().width-4, 12) + framed);
    }

    float l = MathHelper::GetVecLength(_arms[_curArmType]._bulletPos);
    float a = MathHelper::Rad2Deg(MathHelper::Vec2Ang(_arms[_curArmType]._bulletPos));
    if(!GetDir()) {
        a *= -1;
        a -= 180;
    }
    sf::Vector2f newRelPos = MathHelper::Ang2Vec(MathHelper::Deg2Rad(a+_arm.getRotation()))*l;
    _weapon->SetRelPosition(_arm.getPosition() - GetGlobalUpperLeftPos() + newRelPos/*+ _arms[_curArmType]._bulletPos*/);
    _weapon->Update(ip, eTime, bManager, eManager, level, pManager);

    if(_regen > 0) {
        if(_regenTimer.getElapsedTime().asMilliseconds() >= 1000/_regen) {
            _regenTimer.restart();
            SetHP(GetHP()+1);
        }
    }

    if(_groundAttackLevel > 0) {
        float minSpd = (_groundAttackLevel == 1 ? .8 : (_groundAttackLevel == 2 ? .5 : .4));
        if(GetVel().y > minSpd) {
            float time(_groundAttackTimer.getElapsedTime().asMilliseconds());
            if(time > 5) {
                int nbParts(time / 5.f);
                _groundAttackTimer.restart();
                for(int i=0 ; i<nbParts ; i++) {
                    float intx(float(i) / float(nbParts));
                    sf::Vector2f pos(GetGlobalUpperLeftPos() + intx*GetVel()*eTime + sf::Vector2f(MathHelper::RandFloat(0, GetGlobalHitbox().width), MathHelper::RandFloat(0, GetGlobalHitbox().height)));
                    Particle *p = new Particle(ip, "groundAttackParticle",
                                   pos,
                                   /*MathHelper::Ang2Vec(MathHelper::Deg2Rad(ang + MathHelper::RandFloat(-20, 20))) * spd * MathHelper::RandFloat(0.7, 1.2)*/sf::Vector2f(0, 0),
                                   0,
                                   MathHelper::RandFloat(100, 300),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   128,
                                   0,
                                   false,
                                   false,
                                   false,
                                   sf::IntRect(0, 0, 3, 10), false);
                    pManager.AddParticle(p);
                }
            }
        } else {
            _groundAttackTimer.restart();
        }

        if(/*MathHelper::ABS(GetVel().y) < .01 && */GetVel().y <= 0.01 && _prevVelY > minSpd) {
            if(level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM) || level.GetSpawner().IsOnGround(*this)) {
                if(_groundAttackLevel == 1) {
                    GroundAttackBullet *b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 5), sf::Vector2f(.4, 0), false, 10, .1, false);
                    bManager.AddBullet(b);
                    b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 5), sf::Vector2f(-.4, 0), false, 10, .1, false);
                    b->setScale(-1, 1);
                    bManager.AddBullet(b);
                } else if(_groundAttackLevel == 2) {
                    GroundAttackBullet *b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 5), sf::Vector2f(.4, 0), false, 20, .3, false);
                    bManager.AddBullet(b);
                    b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 5), sf::Vector2f(-.4, 0), false, 20, .3, false);
                    b->setScale(-1, 1);
                    bManager.AddBullet(b);
                } else if(_groundAttackLevel == 3) {
                    GroundAttackBullet *b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 1), sf::Vector2f(.4, 0), false, 50, .6, true);
                    bManager.AddBullet(b);
                    b = new GroundAttackBullet(ip, getPosition()+sf::Vector2f(0, 1), sf::Vector2f(-.4, 0), false, 50, .6, true);
                    b->setScale(-1, 1);
                    bManager.AddBullet(b);
                }
            }
        }
    }

    for(int i=0 ; i<_flies.size() ; i++) {
        _flies[i]->Update(ip, eTime, level, pManager, *this);
        if(_leavingPipe) {
            _flies[i]->setPosition(getPosition());
        }
    }

    _prevVelY = GetVel().y;
}

void Character::Draw(IP& ip) {
    GameEntity::Draw(ip);
    _weapon->Draw(ip);
    ip._renderer->Draw(_arm);
}

void Character::DrawFront(IP& ip) {
    for(int i=0 ; i<_flies.size() ; i++) {
        _flies[i]->Draw(ip);
    }
}

void Character::LoadArm(ArmType t) {
    _arm.setTextureRect(_arms[t]._textureRect);
    _arm.setOrigin(_arms[t]._origin);
    _curArmType = t;
}

void Character::GoLeft(float eTime) {
    GameEntity::GoLeft(eTime);
    if(GetAnims().GetAnimationName() == "idle") {
        GetAnims().SetAnimation("walk");
    }
}

void Character::GoRight(float eTime) {
    GameEntity::GoRight(eTime);
    if(GetAnims().GetAnimationName() == "idle") {
        GetAnims().SetAnimation("walk");
    }
}

void Character::Jump(Level& level, float eTime) {
    if(GameEntity::Jump(level)) {
        _canContinueJump = true;
    }
}

void Character::StopJumping() {
    if(_canContinueJump && GetVel().y < 0) {
        SetVel(sf::Vector2f(GetVel().x, GetVel().y/10.f));
    }
    _canContinueJump = false;
}

void Character::EnterPipe(Level& level) {
    Spawner& s(level.GetSpawner());
    if(!s.CanEnterPipe(*(MovingSprite*)this)) {
        return;
    }
    SetVel(sf::Vector2f(0, 0.1));
    _enteringPipe = true;
    _enterTimer.restart();
}

void Character::LeavePipe() {
    _leavingPipe = true;
    SetVel(sf::Vector2f(0, 0.1));
}

bool Character::EnteringPipe() {
    return _enteringPipe;
}

void Character::Hit(Ennemy *other, IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    GameEntity::Hit((GameEntity*)other, ip, pManager, sf::Color(255, 255, 0), MathHelper::RandInt(2, 5), eManager, level);
    if(!other->IsAlive()) {
        EarnXP(other->GetXP());
        level.SetDifficulty(level.GetDifficulty() + other->GetIncDifficulty());
    }
}

void Character::Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level) {
    GameEntity::Damage(dmg, ip, pManager, color, pos, dir, eManager, level);

    //some blood
    float ang = MathHelper::Rad2Deg(MathHelper::Vec2Ang(dir));
    float spd = MathHelper::GetVecLength(dir);
    for(int i=0 ; i<5 ; i++) {
        Particle *p = new Particle(ip, "blood1",
                                   pos,
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(ang + MathHelper::RandFloat(-20, 20))) * spd * MathHelper::RandFloat(0.7, 1.2),
                                   0,
                                   MathHelper::RandFloat(100, 500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   255,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(2, 1, 2, 2), false);
        p->GetAnims().AddAnimation("base", Animation(7, 50, sf::Vector2i(0, 0), sf::Vector2i(6, 6), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
        p = 0;
    }

    for(int i=0 ; i<10 ; i++) {
        Particle *p = new Particle(ip, "blood0",
                                   pos,
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(ang + MathHelper::RandFloat(-20, 20))) * spd * MathHelper::RandFloat(0.7, 1.2),
                                   0,
                                   MathHelper::RandFloat(100, 500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   255,
                                   true,
                                   true,
                                   true,
                                   sf::IntRect(1, 0, 2, 1), false);
        p->GetAnims().AddAnimation("base", Animation(6, 50, sf::Vector2i(0, 0), sf::Vector2i(4, 4), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
        p = 0;
    }
}

void Character::EarnXP(int amount) {
    std::cout << "Earned " << amount << " XP!" << std::endl;
    _xp += amount;
    while(_xp >= _nextXP) {
        LevelUp();
    }
    std::cout << _xp << "/" << _nextXP << "XP" << std::endl;
}

void Character::LevelUp() {
    _level++;
    _xp -= _nextXP;
    _nextXP *= 1.3f;

    float hpRatio(float(GetHP())/float(GetHPMax()));
    _baseHP = 20*pow(1.2, _level);
    SetHPMax(_baseHP*_hpMult);
    SetHP(GetHPMax()*hpRatio);

    std::cout << "Level up! Level " << _level << std::endl;
}

int Character::GetXP() const {
    return _xp;
}

int Character::GetNextXP() const {
    return _nextXP;
}

int Character::GetLevel() const {
    return _level;
}

void Character::SetHPMultiplier(float mult) {
    _hpMult = mult;
    float hpRatio(float(GetHP())/float(GetHPMax()));
    SetHPMax(_baseHP*_hpMult);
    SetHP(GetHPMax()*hpRatio);
}

void Character::SetSpeedMultiplier(float mult) {
    SetSpeed(_baseSpeed*mult);
}

void Character::SetRegen(float regen) {
    _regen = regen;
}

void Character::SetJumpMultiplier(float mult) {
    SetJumpPower(_baseJump * sqrt(mult));
}

void Character::SetReloadSpeedMultiplier(float mult) {
    _weapon->SetReloadSpeedMultiplier(mult);
}

void Character::SetDamageMultiplier(float mult) {
    _weapon->SetDamageMultiplier(mult);
}

void Character::SetGroundAttackLevel(int lvl) {
    _groundAttackLevel = lvl;
}

void Character::AddFlies(IP& ip, int nb) {
    for(int i=0 ; i<nb ; i++) {
        _flies.push_back(new HealingFly(ip));
        _flies[_flies.size()-1]->setPosition(getPosition() + sf::Vector2f(.1, .1));
    }
}

int Character::GetNbFlies() {
    return _flies.size();
}

void Character::Heal(IP& ip, ParticleManager& pManager, float amount) {
    SetHP(GetHP() + amount);
    pManager.AddParticle(new HealingParticle(ip, amount, getPosition()));
}
