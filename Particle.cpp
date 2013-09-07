#include "Particle.h"
#include "IP.h"
#include "Level.h"
#include "MathHelper.h"

Particle::Particle(IP& ip, string name, sf::Vector2f pos, sf::Vector2f velocity, float rotVel, float lifeTime, sf::Vector2f startScale, sf::Vector2f endScale, bool gravity, bool collision, sf::IntRect hitbox) : MovingSprite(ip, name, hitbox) {
    _alive = true;
    _gravity = gravity;
    _collision = collision;
    setPosition(pos);
    SetVel(velocity);
    _lifeTime = lifeTime;
    _startScale = startScale;
    _endScale = endScale;
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
}

Particle::~Particle() {

}

void Particle::Update(IP& ip, float eTime, Level& level) {
    float lifePos = _timer.getElapsedTime().asMilliseconds()/_lifeTime;
    if(lifePos >= 1) {
        _alive = false;
    }
    setScale(MathHelper::Interpolate(lifePos, _startScale, _endScale));
    if(_collision) {
        MovingSprite::Update(ip, eTime, level);
    } else {
        MovingSprite::Update(ip, eTime);
    }

    if(_gravity) {
        Accelerate(sf::Vector2f(0, 0.001), eTime);
    }

    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
}

bool Particle::IsAlive() {
    return _alive;
}
