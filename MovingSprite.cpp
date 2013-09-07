#include "MovingSprite.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Spawner.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"

MovingSprite::MovingSprite(IP& ip, string name) : sf::Sprite() {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
    _hitbox = getTextureRect();
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
}

MovingSprite::MovingSprite(IP& ip, string name, sf::IntRect hitbox) {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(MathHelper::GetCenter(sf::FloatRect(hitbox)));
    _hitbox = hitbox;
    _animTable = new AnimationTable();
    _animTable->AddAnimation("base", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(getTextureRect().width, getTextureRect().height), false));
    _animTable->SetAnimation("base");
}

MovingSprite::~MovingSprite() {
    delete _animTable;
}

void MovingSprite::Update(IP& ip, float eTime) {
    setPosition(getPosition() + GetVel()*eTime);
    setRotation(getRotation() + GetRotVel()*eTime);
    _animTable->Update();
    setTextureRect(_animTable->GetRect());
}

void MovingSprite::Update(IP& ip, float eTime, Level& level) {
    sf::Vector2f delta = GetVel()*eTime;
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
    _animTable->Update();
    setTextureRect(_animTable->GetRect());
}

bool MovingSprite::TryMove(sf::Vector2f delta, Level& level) {
    if(level.GetMap().IsCollided(*this, GetUpperLeftPos()+delta) || level.GetSpawner().IsCollided(*this, GetUpperLeftPos()+delta)) {
        return false;
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

void MovingSprite::SetVel(sf::Vector2f vel) {
    _vel = vel;
}

void MovingSprite::Accelerate(sf::Vector2f vec, float eTime) {
    SetVel(GetVel() + vec*eTime);
}

void MovingSprite::SetRotVel(float rotVel) {
    _rotVel = rotVel;
}

void MovingSprite::SetHitbox(sf::IntRect rect) {
    _hitbox = rect;
}
