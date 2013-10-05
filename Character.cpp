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
#include "Bow.h"
#include "Particle.h"

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(2, 2, 9, 27), 10) {
    SetWeight(0.5f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(13, 29), true));
    t.AddAnimation("attack", new Animation(1, 50, sf::Vector2i(0, 29), sf::Vector2i(13, 29), false));
    t.SetAnimation("idle");
    _enteringPipe = false;
    _leavingPipe = false;

    _level = 0;
    _xp = 0;
    _nextXP = 10;

    _weapon = new Bow(ip, (const GameEntity&)*this);
    //_weapon = new Weapon(ip, "bow", sf::IntRect(0, 0, 7, 17), *this, sf::Vector2f(5, 4), 500);
}

Character::~Character() {
    /*delete _weapon;
    _weapon = 0;*/
}

void Character::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    if(_enteringPipe) {
        SetVel(sf::Vector2f(0, 0.1));
        MovingSprite::Update(ip, eTime);
        if(_enterTimer.getElapsedTime().asMilliseconds() > 500) {
            _enteringPipe = false;
            level.NextLevel(ip, eManager, bManager, *this);
            _leavingPipe = true;
            _enterTimer.restart();
        }
    } else if (_leavingPipe) {
        SetVel(sf::Vector2f(0, 0.1));
        MovingSprite::Update(ip, eTime);
        if(!level.GetSpawner().IsCollided(*this)) {
            _enterTimer.restart();
            _leavingPipe = false;
        }
    } else {
        if(GetAnims().GetAnimationName()=="idle") {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                GetAnims().SetAnimation("attack");
                _weapon->Use(ip, bManager);

                for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
                    sf::FloatRect attackRect;
                    if(GetDir()) {
                        attackRect = sf::FloatRect(GetGlobalHitbox().left+GetGlobalHitbox().width, GetGlobalHitbox().top, 16, GetGlobalHitbox().height);
                    } else {
                        attackRect = sf::FloatRect(GetGlobalHitbox().left-16, GetGlobalHitbox().top, 16, GetGlobalHitbox().height);
                    }
                    if(eManager.GetEnnemy(i)->GetGlobalHitbox().intersects(attackRect)) {
                        Hit(eManager.GetEnnemy(i), ip, pManager, level);
                    }
                }
            }
        } else {
            if(GetAnims().GetAnimation().IsFinished()) {
                GetAnims().SetAnimation("idle");
            }
        }

        GameEntity::Update(ip, eTime, level, eManager, pManager);
    }

    _weapon->Update(ip, eTime, bManager);
}

void Character::Draw(IP& ip) {
    GameEntity::Draw(ip);
    _weapon->Draw(ip);
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

bool Character::EnteringPipe() {
    return _enteringPipe;
}

void Character::Hit(Ennemy *other, IP& ip, ParticleManager& pManager, Level& level) {
    GameEntity::Hit((GameEntity*)other, ip, pManager, sf::Color(255, 255, 0));
    if(!other->IsAlive()) {
        EarnXP(other->GetXP());
        level.SetDifficulty(level.GetDifficulty() + other->GetIncDifficulty());
    }
}

void Character::Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir) {
    GameEntity::Damage(dmg, ip, pManager, color, pos, dir);

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
                                   sf::IntRect(2, 1, 2, 2));
        p->GetAnims().AddAnimation("base", new Animation(7, 50, sf::Vector2i(0, 0), sf::Vector2i(6, 6), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
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
                                   sf::IntRect(1, 0, 2, 1));
        p->GetAnims().AddAnimation("base", new Animation(6, 50, sf::Vector2i(0, 0), sf::Vector2i(4, 4), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
}

void Character::EarnXP(int amount) {
    _xp += amount;
    if(_xp >= _nextXP) {
        LevelUp();
    }
    cout << _xp << "/" << _nextXP << "XP" << endl;
}

void Character::LevelUp() {
    _level++;
    _xp -= _nextXP;
    _nextXP *= 1.3f;

    SetHPMax(GetHPMax() * 1.2f);
    SetHP(GetHPMax());

    cout << "Level up! Level " << _level << endl;
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
