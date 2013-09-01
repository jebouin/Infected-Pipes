#include "MovingSprite.h"
#include "IP.h"
#include "Map.h"
#include "TextureLoader.h"
#include "MathHelper.h"

MovingSprite::MovingSprite(IP& ip, string name) : sf::Sprite() {
    _vel = sf::Vector2f(0, 0);
    _rotVel = 0;
    setTexture(ip._textureLoader->GetTexture(name));
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
}

MovingSprite::~MovingSprite() {

}

void MovingSprite::Update(IP& ip, float eTime) {
    setPosition(getPosition() + GetVel()*eTime);
    setRotation(getRotation() + GetRotVel()*eTime);
}

void MovingSprite::Update(IP& ip, float eTime, Map& map) {
    sf::Vector2f delta = GetVel()*eTime;
    if(!TryMove(delta, map)) {
        for(float i=0.1f ; i<MathHelper::ABS(delta.x)-0.1f ; i+=0.1f) {
            if(!TryMove(sf::Vector2f(MathHelper::SGN(delta.x)/10.f, 0), map)) {
                SetVel(sf::Vector2f(0, GetVel().y));
                break;
            }
        }
        for(float i=0.1f ; i<MathHelper::ABS(delta.y)-0.1f ; i+=0.1f) {
            if(!TryMove(sf::Vector2f(0, MathHelper::SGN(delta.y)/10.f), map)) {
                SetVel(sf::Vector2f(GetVel().x, 0));
                break;
            }
        }
    }
}

bool MovingSprite::TryMove(sf::Vector2f delta, Map& map) {
    if(map.IsCollided(*this, GetUpperLeftPos()+delta)) {
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

void MovingSprite::SetVel(sf::Vector2f vel) {
    _vel = vel;
}

void MovingSprite::Accelerate(sf::Vector2f vec, float eTime) {
    SetVel(GetVel() + vec*eTime);
}

void MovingSprite::SetRotVel(float rotVel) {
    _rotVel = rotVel;
}
