#include "FireWormBoss.h"
#include "Level.h"
#include "Character.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Renderer.h"
#include "IP.h"
#include "MathHelper.h"
#include "Map.h"
#include "Bullet.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "ResourceLoader.h"
#include "DualFireBullet.h"
#include "WaterField.h"

FireWormBoss::FireWormBoss(IP& ip, Level& level)
    : Ennemy(ip, "fireWormBoss", sf::IntRect(0, 6, 43, 60), 4200, 1000, 500, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("goingup", Animation(1, 300, sf::Vector2i(34, 0), sf::Vector2i(34, 78), false));
    t.AddAnimation("idle", Animation(4, 300, sf::Vector2i(0, 0), sf::Vector2i(34, 78), true));
    t.SetAnimation("goingup");
    SetFlying(true);
    SetPhysics(false);
    SetPushable(false);
    _upY = -40;
    _downY = 38;
    _relY = _downY;
    setPosition(sf::Vector2f(200, 0));
    _stateTime = 1000;
    _curState = SDOWN;

    _turretBase.setTexture(ResourceLoader::GetTexture("fireWormBossTurret"));
    _turretBase.setOrigin(sf::Vector2f(_turretBase.getTextureRect().width/2, _turretBase.getTextureRect().height));
    float baseY = -34;
    _turUpY = 0 + baseY;
    _turDownY = _turretBase.getTextureRect().height+1 + baseY;
    _relTurretY = _turDownY;

    _turretCannon.setTexture(ResourceLoader::GetTexture("fireWormBossCannon"));
    _turretCannon.setOrigin(sf::Vector2f(_turretCannon.getTextureRect().width/2, _turretCannon.getTextureRect().height + 6));
}

FireWormBoss::~FireWormBoss() {

}

void FireWormBoss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    AnimationTable& t(GetAnims());
    Map& map(level.GetMap());
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);

    switch(_curState) {
    case SGOINGUP:
        _relY -= .4f*eTime;
        if(_relY <= _upY) {
            _relY = _upY;
            ChangeState(SUP);
        }
        break;
    case SGOINGDOWN:
        _relY += .3f*eTime;
        if(_relY >= _downY) {
            _relY = _downY;
            ChangeState(SDOWN);
            float xPos=0;
            bool correctPos = false;
            while(!correctPos) {
                xPos = MathHelper::RandFloat(64, map.GetSize().x*16-64);
                if(MathHelper::ABS(xPos - character.getPosition().x) < 200) {
                    correctPos = true;
                }
            }
            setPosition(sf::Vector2f(xPos, getPosition().y));
        }
        break;
    case SUP:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            ChangeState(STURRETGOINGUP);
        }
        break;
    case SDOWN:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            ChangeState(SGOINGUP);
        }
        break;
    case STURRETGOINGUP:
        _relTurretY -= eTime * .07f;
        if(_relTurretY < _turUpY) {
            _relTurretY = _turUpY;
            ChangeState(STURRETATTACKING);
        }
        break;
    case STURRETGOINGDOWN:
        _relTurretY += eTime * .07f;
        if(_relTurretY > _turDownY) {
            _relTurretY = _turDownY;
            ChangeState(SGOINGDOWN);
        }
        //_turretCannon.setRotation(((_relTurretY-_turUpY)/(_turDownY-_turUpY))*(_startCannonAngle + 90) - 90); interpolate pos
        break;
    case STURRETATTACKING:
        if(_stateTimer.getElapsedTime().asMilliseconds() >= _stateTime) {
            _startCannonAngle = _turretCannon.getRotation();
            ChangeState(STURRETGOINGDOWN);
        }
        float angle = MathHelper::Rad2Deg(MathHelper::Vec2Ang(_turretCannon.getPosition()-character.getPosition()));
        _turretCannon.setRotation(angle-90);
        if(_cannonTimer.getElapsedTime().asMilliseconds() >= 300) {
            _cannonTimer.restart();
            DualFireBullet *b = new DualFireBullet(ip, _turretCannon.getPosition(), MathHelper::Ang2Vec(MathHelper::Deg2Rad(_turretCannon.getRotation() - 90))*.4f, true);
            bManager.AddBullet(b);
        }
        break;
    }

    if(_curState == STURRETGOINGUP || _curState == STURRETGOINGDOWN || _curState == STURRETATTACKING) {
        _turretBase.setPosition(getPosition() + sf::Vector2f(-4, _relTurretY));
        _turretCannon.setPosition(_turretBase.getPosition() + sf::Vector2f(0, -_turretBase.getTextureRect().height/2.f));
    }

    //LAVA IS FLOWING OMG!
    if(level.GetNbWaterFields() == 1) {
        WaterField& wf(level.GetWaterField(0));
        wf.SetNormalHeight(wf.GetNormalHeight() + .01f*eTime);
    }

    //get the minumum lava height to set the position relatively to the HUUUUGE lava field :D
    float minLavaY = 0;
    if(level.GetNbWaterFields() == 1) {
        WaterField& wf(level.GetWaterField(0));
        float minX = GetGlobalHitbox().left;
        float maxX = GetGlobalHitbox().left+GetGlobalHitbox().width;
        for(float i=minX ; i<maxX ; i++) {
            float curLavaY = wf.GetY(i);
            if(curLavaY > minLavaY) {
                minLavaY = curLavaY;
            }
        }
    }
    setPosition(sf::Vector2f(getPosition().x, minLavaY+_relY));
}

void FireWormBoss::Draw(IP& ip) {
    if(_curState == STURRETGOINGUP || _curState == STURRETGOINGDOWN || _curState == STURRETATTACKING) {
        ip._renderer->Draw(_turretBase);
        ip._renderer->Draw(_turretCannon);
    }
    Ennemy::Draw(ip);
}

void FireWormBoss::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
}

void FireWormBoss::ChangeState(State state) {
    AnimationTable& t(GetAnims());
    _stateTimer.restart();
    switch(state) {
    case SUP:
        _curState = SUP;
        t.SetAnimation("idle");
        _stateTime = 1000;
        break;
    case SDOWN:
        _curState = SDOWN;
        _stateTime = 1000;
        break;
    case SGOINGUP:
        _curState = SGOINGUP;
        t.SetAnimation("goingup");
        break;
    case SGOINGDOWN:
        _curState = SGOINGDOWN;
        t.SetAnimation("goingup");
        break;
    case STURRETGOINGUP:
        _curState = STURRETGOINGUP;
        break;
    case STURRETATTACKING:
        _curState = STURRETATTACKING;
        _stateTime = 4000;
        break;
    case STURRETGOINGDOWN:
        _curState = STURRETGOINGDOWN;
        break;
    }
}
