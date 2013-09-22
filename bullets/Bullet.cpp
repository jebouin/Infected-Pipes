#include "Bullet.h"
#include "TextureLoader.h"
#include "IP.h"
#include "Level.h"
#include "Renderer.h"
#include "Map.h"
#include "Spawner.h"

Bullet::Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, bool animated) : MovingSprite(ip, name, hitbox, animated) {
    setPosition(position);
    SetVel(vel);
}

Bullet::~Bullet() {

}

void Bullet::Update(IP& ip, float eTime, Level& level) {
    Accelerate(sf::Vector2f(0, 0.001), eTime);

    if(level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetSpawner().IsOnGround(*this)) {
        Accelerate(sf::Vector2f(-0.01*GetVel().x, 0), eTime);
    } else {
        //Accelerate(sf::Vector2f(-0.0003*GetVel().x, 0), eTime);
    }

    MovingSprite::Update(ip, eTime, level);
}

void Bullet::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}
