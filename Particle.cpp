#include "Particle.h"
#include "IP.h"
#include "Level.h"
#include "MathHelper.h"
#include "Map.h"
#include "Spawner.h"
#include "Renderer.h"

Particle::Particle(IP& ip, string name, sf::Vector2f pos, sf::Vector2f velocity, float rotVel, float lifeTime, sf::Vector2f startScale, sf::Vector2f endScale, float startAlpha, float endAlpha, bool gravity, bool collision, bool animated, sf::IntRect hitbox)
    : MovingSprite(ip, name, hitbox, animated) {
    _alive = true;
    _gravity = gravity;
    _collision = collision;
    setPosition(pos);
    SetVel(velocity);
    SetRotVel(rotVel);
    _lifeTime = lifeTime;
    _startScale = startScale;
    _endScale = endScale;
    _startAlpha = startAlpha;
    _endAlpha = endAlpha;
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);
}

Particle::~Particle() {

}

void Particle::Update(IP& ip, float eTime, Level& level, ParticleManager& pManager) {
    bool inWater = IsInWater(level);
    float lifePos = _timer.getElapsedTime().asMilliseconds()/_lifeTime;
    if(lifePos >= 1) {
        _alive = false;
    }
    if(!_alive) {
        return;
    }
    setScale(MathHelper::Interpolate(lifePos, _startScale, _endScale));
    setColor(sf::Color(getColor().r, getColor().g, getColor().b, MathHelper::Interpolate(lifePos, _startAlpha, _endAlpha)));
    if(_collision) {
        MovingSprite::Update(ip, eTime, level, pManager);
    } else {
        MovingSprite::Update(ip, eTime);
    }

    if(_gravity && !inWater) {
        Accelerate(sf::Vector2f(0, 0.001), eTime);
        if(level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetSpawner().IsOnGround(*this)) {
            SetVel(sf::Vector2f(GetVel().x/1.1f, GetVel().y));
        }
    }
    if(inWater) {
        Accelerate(sf::Vector2f(-0.004*GetVel().x, -0.004*GetVel().y), eTime);
    }

    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height)/2.f);

    //bounce
    /*if(_collision) {
        float dirx = MathHelper::ABS(GetVel().x)/GetVel().x;
        float diry = MathHelper::ABS(GetVel().y)/GetVel().y;
        sf::Vector2f tpx = sf::Vector2f(dirx, 0)+GetUpperLeftPos();
        sf::Vector2f tpy = sf::Vector2f(0, diry)+GetUpperLeftPos();
        if(level.GetMap().IsCollided(*this, tpx, Map::WALL) || level.GetSpawner().IsCollided(*this, tpx)) {
            SetVel(sf::Vector2f(-GetVel().x, GetVel().y));
        }
        if(level.GetMap().IsCollided(*this, tpy, Map::WALL) || level.GetSpawner().IsCollided(*this, tpy)) {
            SetVel(sf::Vector2f(GetVel().x, -GetVel().y));
        }
    }*/
}

void Particle::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}

bool Particle::IsAlive() {
    return _alive;
}
