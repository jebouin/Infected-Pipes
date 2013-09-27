#include "Bullet.h"
#include "TextureLoader.h"
#include "IP.h"
#include "Level.h"
#include "Renderer.h"
#include "Map.h"
#include "Spawner.h"
#include "Character.h"
#include "ParticleManager.h"
#include "GameEntity.h"

Bullet::Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, bool animated) : MovingSprite(ip, name, hitbox, animated) {
    setPosition(position);
    SetVel(vel);
    _alive = true;
    _dying = false;
}

Bullet::~Bullet() {

}

void Bullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager) {
    Accelerate(sf::Vector2f(0, 0.001), eTime);

    if(level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM) || level.GetSpawner().IsOnGround(*this)) {
        Accelerate(sf::Vector2f(-0.01*GetVel().x, 0), eTime);
    } else {
        //Accelerate(sf::Vector2f(-0.0003*GetVel().x, 0), eTime);
    }

    if((level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM)) && !_dying) {
        _dying = true;
        _deadTimer.restart();
    }
    if(_dying) {
        float deadTime = _deadTimer.getElapsedTime().asMilliseconds();
        setColor(sf::Color(getColor().r, getColor().g, getColor().b, 255-deadTime/1000.f*255));
        if(deadTime > 1000) {
            _alive = false;
        }
    }

    MovingSprite::Update(ip, eTime, level);

    if(!_dying && GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
        Impact((GameEntity&)(character), ip, pManager, sf::Color(255, 0, 0));
    }
}

void Bullet::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}

void Bullet::Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color) {
    _dying = true;
    _deadTimer.restart();
    entity.Damage(2, ip, pManager, color);
}

bool Bullet::IsAlive() const {
    return _alive;
}
