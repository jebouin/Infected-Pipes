#include "SnowMan.h"
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

SnowMan::SnowMan(IP& ip, Level& level) : Ennemy(ip, "snowMan", sf::IntRect(16, 3, 14, 29), 192, 25, 30, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", Animation(4, 80, sf::Vector2i(0, 0), sf::Vector2i(45, 33), true));
    t.AddAnimation("attackingR", Animation(6, 70, sf::Vector2i(0, 33), sf::Vector2i(26, 31), true));
    t.AddAnimation("attackingL", Animation(6, 70, sf::Vector2i(0, 64), sf::Vector2i(26, 31), true));
    t.SetAnimation("idle");
    SetSpeed(.002);
    SetJumpPower(.7);
    SetWeight(0.6f);
    _stateTime = 2000;
    _curState = WALKING;
}

SnowMan::~SnowMan() {

}

void SnowMan::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& t(GetAnims());
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    Map& m(level.GetMap());

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(20, 24), eManager, level);
        _attackTimer.restart();
    }

    switch(_curState) {
    case IDLE:

        break;
    case WALKING:
        if(_jumpTimer.getElapsedTime().asMilliseconds() >= 700) {
            _jumpTimer.restart();
            Jump(level);
        }
        if(IsInWater(level)) {
            Jump(level);
        } else {
            if(!level.GetMap().IsOnTileType(*this, Map::WALL) && !level.GetSpawner().IsOnGround(*this) && !level.GetMap().IsOnTileType(*this, Map::PLATFORM)) {
                if(getPosition().x > character.getPosition().x) {
                    GoLeft(eTime);
                } else {
                    GoRight(eTime);
                }
            }
        }
        break;
    case ATT:
        if(!GetDir()) {
            ChangeDir();
        }
        bool attdir = true;
        if(character.getPosition().x > getPosition().x) {
            if(t.GetAnimationName() != "attackingR") {
                t.SetAnimation("attackingR");
                SetHitbox(sf::IntRect(2, 2, 18, 28));
            }
            attdir = true;
        } else {
            if(t.GetAnimationName() != "attackingL") {
                t.SetAnimation("attackingL");
                SetHitbox(sf::IntRect(6, 2, 18, 28));
            }
            attdir = false;
        }
        if(_ballTimer.getElapsedTime().asMilliseconds() >= 100 && t.GetAnimation().GetCurFrame() == 0) {
            _ballTimer.restart();
            sf::Vector2f rp = (attdir ? sf::Vector2f(-2, -5) : sf::Vector2f(-8, 0));
            sf::Vector2f vel = MathHelper::Ang2Vec(MathHelper::Deg2Rad(attdir ? MathHelper::RandFloat(-40, -10) : MathHelper::RandFloat(190, 220))) * MathHelper::RandFloat(.2, .4);
            Bullet *b = new Bullet(ip, "snowBallBullet", sf::IntRect(1, 1, 6, 6), getPosition()+rp, vel, 24, .1, false, true, true, true, false, true, false, 0);
            bManager.AddBullet(b);
        }
        break;
    }

    if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
        _stateTimer.restart();
        if(rand()%2) {
            if(MathHelper::GetVecLength(getPosition()-character.getPosition()) < 500) {
                _curState = ATT;
                _stateTime = 2500;
            } else {
                _curState = IDLE;
                _stateTime = 1500;
                t.SetAnimation("idle");
            }
        } else {
            _curState = WALKING;
            _stateTime = 4000;
            t.SetAnimation("idle");
            SetHitbox(sf::IntRect(16, 3, 14, 29));
        }
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void SnowMan::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
}
