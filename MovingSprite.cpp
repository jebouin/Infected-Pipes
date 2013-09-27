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

MovingSprite::MovingSprite(IP& ip, string name, bool animated) : sf::Sprite() {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
    _hitbox = getTextureRect();
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
    _animated = animated;
    _onPlatform = false;
    _box.setPointCount(4);
}

MovingSprite::MovingSprite(IP& ip, string name, sf::IntRect hitbox, bool animated) {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(MathHelper::GetCenter(sf::FloatRect(hitbox)));
    _hitbox = hitbox;
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
    _animated = animated;
    _onPlatform = false;
    _box.setPointCount(4);
}

MovingSprite::~MovingSprite() {
    delete _animTable;
}

void MovingSprite::Update(IP& ip, float eTime) {
    setPosition(getPosition() + GetVel()*eTime);
    setRotation(getRotation() + GetRotVel()*eTime);
    if(_animated) {
        _animTable->Update();
        setTextureRect(_animTable->GetRect());
    }
}

void MovingSprite::Update(IP& ip, float eTime, Level& level) {
    sf::Vector2f delta = GetVel()*eTime;
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
}

void MovingSprite::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    //ip._renderer->Draw(_box);
}

void MovingSprite::MoveCollidingMap(sf::Vector2f delta, Level& level) {
    //cout << delta.x << " " << delta.y << endl;
    if(MathHelper::GetVecLength(delta) > 2) {
        for(int i=0 ; i<2 ; i++)
            MoveCollidingMap(delta/2.f, level);
        return;
    }
    if(!TryMove(delta, level)) {
        for(float i=0.1f ; i<MathHelper::ABS(delta.x)-0.1f ; i+=0.1f) {
            if(!TryMove(sf::Vector2f(MathHelper::SGN(delta.x)/10.f, 0), level)) {
                SetVel(sf::Vector2f(0, GetVel().y));
                break;
            }
        }
        for(float i=0.1f ; i<MathHelper::ABS(delta.y)-0.1f ; i+=0.1f) {
            if(!TryMove(sf::Vector2f(0, MathHelper::SGN(delta.y)/10.f), level)) {
                SetVel(sf::Vector2f(GetVel().x, 0));
                break;
            }
        }
    }
}

bool MovingSprite::TryMove(sf::Vector2f delta, Level& level) {
    if(level.GetMap().IsCollided(*this, GetUpperLeftPos()+delta, Map::WALL) || level.GetSpawner().IsCollided(*this, GetUpperLeftPos()+delta)) {
        return false;
    }
    if(GetVel().y >= 0 && !((int)(GetGlobalHitbox().top + GetGlobalHitbox().height + delta.y)%16 > 3)) {
        if(level.GetMap().IsOnTileType(*this, GetUpperLeftPos()+delta, Map::PLATFORM)) {
            return false;
        }
    }
    setPosition(getPosition() + delta);
    return true;
}

sf::Vector2f MovingSprite::GetVel() {
    return _vel;
}

float MovingSprite::GetRotVel() {
    return _rotVel;
}

sf::Vector2f MovingSprite::GetUpperLeftPos() {
    return sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top);
}

sf::IntRect MovingSprite::GetHitbox() {
    return _hitbox;
}

sf::FloatRect MovingSprite::GetGlobalHitbox() {
    return sf::FloatRect(sf::Vector2f(_hitbox.left, _hitbox.top)+GetUpperLeftPos(), sf::Vector2f(_hitbox.width, _hitbox.height));
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
    sf::Vector2f delta = getPosition() - GetUpperLeftPos();
    setPosition(pos + delta);
}

void MovingSprite::SetHitbox(sf::IntRect rect) {
    _hitbox = rect;
}

void MovingSprite::SetOnPlatform(bool on) {
    _onPlatform = on;
}
