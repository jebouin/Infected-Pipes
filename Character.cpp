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
#include "TextureLoader.h"

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(4, 3, 7, 27), 10) {
    SetWeight(0.5f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", new Animation(8, 100, sf::Vector2i(0, 0), sf::Vector2i(15, 31), true));
    t.AddAnimation("idle", new Animation(1, 50, sf::Vector2i(0, 31), sf::Vector2i(15, 31), false));
    t.SetAnimation("walk");
    _enteringPipe = false;
    _leavingPipe = false;

    _level = 0;
    _xp = 0;
    _nextXP = 10;

    _weapon = new Bow(ip, (const GameEntity&)*this);

    _arm.setTexture(ip._textureLoader->GetTexture("arm"));
    _arm.setOrigin(sf::Vector2f(2, 1));

    SetAutoDir(false);
}

Character::~Character() {
    /*delete _weapon;
    _weapon = 0;*/
}

void Character::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::Vector2f mpos = MathHelper::GetMousePos(ip);
    AnimationTable& t(GetAnims());

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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _weapon->Use(ip, bManager);
        }
        GameEntity::Update(ip, eTime, level, eManager, pManager);
        float r = MathHelper::Rad2Deg(MathHelper::Vec2Ang(mpos-_arm.getPosition()));
        if(!GetDir()) {
            _arm.setScale(-1, 1);
            r -= 180;
        } else {
            _arm.setScale(1, 1);
        }
        _arm.setRotation(r);
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
        _arm.setPosition(GetUpperLeftPos() + sf::Vector2f(4, 12) + framed);
    } else {
        if(mpos.x > _arm.getPosition().x) {
            ChangeDir();
        }
        _arm.setPosition(GetUpperLeftPos() + sf::Vector2f(getLocalBounds().width-4, 12) + framed);
    }
    _weapon->Update(ip, eTime, bManager);
}

void Character::Draw(IP& ip) {
    GameEntity::Draw(ip);
    //_weapon->Draw(ip);
    ip._renderer->Draw(_arm);
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
