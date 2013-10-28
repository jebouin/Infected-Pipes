#include "MovingSprite.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Spawner.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "Renderer.h"
#include "WaterField.h"
#include "ParticleManager.h"

MovingSprite::MovingSprite(IP& ip, string name, bool animated) : sf::Sprite() {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    _hitbox = getTextureRect();
    setOrigin(sf::Vector2f(sf::Vector2i(MathHelper::GetCenter(sf::FloatRect(_hitbox)))));
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
    _animated = animated;
    _onPlatform = false;
    _box.setPointCount(4);
    _collidesWithPlatform = true;
    _collidesWithWater = true;
    _collisionPrecision = .2;
}

MovingSprite::MovingSprite(IP& ip, string name, sf::IntRect hitbox, bool animated) {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(sf::Vector2f(sf::Vector2i(MathHelper::GetCenter(sf::FloatRect(hitbox)))));
    _hitbox = hitbox;
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
    _animated = animated;
    _onPlatform = false;
    _box.setPointCount(4);
    _collidesWithPlatform = true;
    _collidesWithWater = true;
    _collisionPrecision = .2;
}

MovingSprite::~MovingSprite() {
    delete _animTable;
    _animTable = 0;
}

void MovingSprite::Update(IP& ip, float eTime) {
    setPosition(getPosition() + GetVel()*eTime);
    setRotation(getRotation() + GetRotVel()*eTime);
    if(_animated) {
        _animTable->Update();
        setTextureRect(_animTable->GetRect());
    }
}

void MovingSprite::Update(IP& ip, float eTime, Level& level, ParticleManager& pManager) {
    sf::Vector2f delta = GetVel()*eTime;
    sf::Vector2f deltaPos = getPosition()-_prevPos;
    if(MathHelper::GetVecLength(deltaPos) > 1)
        _prevPos = getPosition();
    MoveCollidingMap(delta, level);
    if(_animated) {
        _animTable->Update();
        setTextureRect(_animTable->GetRect());
    }
    setRotation(getRotation() + GetRotVel()*eTime);
    if(level.GetMap().IsOnTileType(*this, Map::PLATFORM) && GetVel().y >= 0) {
        _onPlatform = true;
    } else {
        _onPlatform = false;
    }

    vector<sf::Vector2f> boxCorners = MathHelper::Rect2Corners(GetGlobalHitbox());
    for(int i=0 ; i<4 ; i++) {
        _box.setPoint(i, boxCorners[i]);
    }

    WaterCollision(level, delta, pManager, ip);
}

void MovingSprite::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    //ip._renderer->Draw(_box);
}

void MovingSprite::MoveCollidingMap(sf::Vector2f delta, Level& level) {
    if(MathHelper::GetVecLength(delta) > 3) {
        for(int i=0 ; i<2 ; i++)
            MoveCollidingMap(delta/2.f, level);
        return;
    }
    float p = _collisionPrecision;
    if(!TryMove(delta, level)) {
        for(float i=p ; i<MathHelper::ABS(delta.x)-p ; i+=p) {
            if(!TryMove(sf::Vector2f(MathHelper::SGN(delta.x)/(1./p), 0), level)) {
                SetVel(sf::Vector2f(0, GetVel().y));
                SetRotVel(GetRotVel()/2.f);
                break;
            }
        }
        for(float i=p ; i<MathHelper::ABS(delta.y)-p ; i+=p) {
            if(!TryMove(sf::Vector2f(0, MathHelper::SGN(delta.y)/(1./p)), level)) {
                SetVel(sf::Vector2f(GetVel().x, 0));
                SetRotVel(GetRotVel()/2.f);
                break;
            }
        }
    }
}

bool MovingSprite::TryMove(sf::Vector2f delta, Level& level) {
    if(level.GetMap().IsCollided(*this, GetGlobalUpperLeftPos()+delta, Map::WALL) || level.GetSpawner().IsCollided(*this, GetGlobalUpperLeftPos()+delta)) {
        return false;
    }
    if(GetVel().y >= 0 && !((int)(GetGlobalHitbox().top + GetGlobalHitbox().height + delta.y)%16 > 3) && _collidesWithPlatform) {
        if(level.GetMap().IsOnTileType(/*this, GetUpperLeftPos()+delta*/ sf::FloatRect(GetGlobalUpperLeftPos().x+GetHitbox().left+delta.x, GetGlobalUpperLeftPos().y+GetHitbox().top+GetGlobalHitbox().height-12+delta.y, GetGlobalHitbox().width, 12), Map::PLATFORM)) {
            return false;
        }
    }
    setPosition(getPosition() + delta);
    return true;
}

void MovingSprite::WaterCollision(Level& level, sf::Vector2f deltaPos, ParticleManager& pManager, IP& ip) {
    if(!_collidesWithWater) {
        return;
    }
    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& w(level.GetWaterField(i));
        sf::FloatRect r(w.GetRect());

        if(r.intersects(GetGlobalHitbox()) && !r.intersects(sf::FloatRect(GetGlobalHitbox().left-deltaPos.x, GetGlobalHitbox().top-deltaPos.y, GetGlobalHitbox().width, GetGlobalHitbox().height))) {
            w.Splash(getPosition(), -GetVel().y*100, pManager, ip);
        }
    }
}

bool MovingSprite::IsInWater(Level& level) {
    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& w(level.GetWaterField(i));
        sf::FloatRect r(w.GetRect());

        if(/*r.intersects(GetGlobalHitbox())*/r.contains(getPosition())) {
            return true;
        }
    }
    return false;
}

bool MovingSprite::GetCollidesWithWater() {
    return _collidesWithWater;
}

sf::Vector2f MovingSprite::GetVel() {
    return _vel;
}

float MovingSprite::GetRotVel() {
    return _rotVel;
}

sf::Vector2f MovingSprite::GetLocalUpperLeftPos() const {
    return getPosition() - sf::Vector2f(getLocalBounds().width/2.f, getLocalBounds().height/2.f);
}

sf::Vector2f MovingSprite::GetGlobalUpperLeftPos() const {
    return sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top);
}

sf::IntRect MovingSprite::GetHitbox() {
    return _hitbox;
}

sf::FloatRect MovingSprite::GetGlobalHitbox() {
    return sf::FloatRect(sf::Vector2f(_hitbox.left, _hitbox.top)+GetGlobalUpperLeftPos(), sf::Vector2f(_hitbox.width, _hitbox.height));
}

AnimationTable& MovingSprite::GetAnims() {
    return *_animTable;
}

bool MovingSprite::OnPlatform() {
    return _onPlatform;
}

void MovingSprite::SetVel(sf::Vector2f vel) {
    _vel = vel;
}

void MovingSprite::Accelerate(sf::Vector2f vec, float eTime) {
    SetVel(GetVel() + vec*eTime);
}

void MovingSprite::SetRotVel(float rotVel) {
    _rotVel = rotVel;
}

void MovingSprite::SetUpperLeftCorner(sf::Vector2f pos) {
    sf::Vector2f delta = getPosition() - GetGlobalUpperLeftPos();
    setPosition(pos + delta);
}

void MovingSprite::SetHitbox(sf::IntRect rect) {
    _hitbox = rect;
}

void MovingSprite::SetOnPlatform(bool on) {
    _onPlatform = on;
}

void MovingSprite::SetCollideOnPlatform(bool c) {
    _collidesWithPlatform = c;
}

void MovingSprite::SetCollideWithWater(bool c) {
    _collidesWithWater = c;
}

void MovingSprite::SetCollisionPrecision(float p) {
    _collisionPrecision = p;
}
