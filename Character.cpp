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

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(2, 0, 7, 26), 10) {
    SetWeight(0.5f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(22, 26), true));
    t.AddAnimation("attack", new Animation(1, 50, sf::Vector2i(0, 26), sf::Vector2i(22, 26), false));
    t.SetAnimation("idle");
    _enteringPipe = false;
    _leavingPipe = false;

    _level = 0;
    _xp = 0;
    _nextXP = 10;
}

Character::~Character() {

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
        return;
    } else if (_leavingPipe) {
        SetVel(sf::Vector2f(0, 0.1));
        MovingSprite::Update(ip, eTime);
        if(!level.GetSpawner().IsCollided(*this)) {
            _enterTimer.restart();
            _leavingPipe = false;
        }
        return;
    }

    if(GetAnims().GetAnimationName()=="idle") {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            GetAnims().SetAnimation("attack");
            /*Bullet *b = new Bullet(ip, "littleRockBullet", sf::IntRect(0, 0, 5, 5),
                                   MathHelper::GetCenter(GetGlobalHitbox()),
                                   MathHelper::Ang2Vec(MathHelper::Vec2Ang(sf::Vector2f(ip._renderer->GetTexture().convertCoords(sf::Vector2i(MathHelper::GetMousePos(*(ip._window))))) - MathHelper::GetCenter(GetGlobalHitbox()))) * MathHelper::RandFloat(0.4, 0.6),
                                   false);
            bManager.AddBullet(b);*/

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

    //if(rand()%(max(300-GetLevel()*20, 10))==0) Damage(1, ip, pManager);

    GameEntity::Update(ip, eTime, level, eManager, pManager);
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
    GameEntity::Hit((GameEntity*)other, ip, pManager);
    if(!other->IsAlive()) {
        EarnXP(other->GetXP());
        level.SetDifficulty(level.GetDifficulty() + other->GetIncDifficulty());
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
