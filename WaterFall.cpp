#include "WaterFall.h"
#include "IP.h"
#include "Renderer.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"

WaterFall::WaterFall(IP& ip, sf::Vector2i tilePos)
    : MovingSprite(ip, "waterFall", sf::IntRect(0, 0, 6, 16), true) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("fall", new Animation(8, 30, sf::Vector2i(0, 0), sf::Vector2i(6, 16), true));
    t.SetAnimation("fall");
    setPosition(sf::Vector2f(tilePos*16) + sf::Vector2f(8, 1));
}

WaterFall::~WaterFall() {

}

void WaterFall::Update(IP& ip, float elapsedTime, Level& level) {
    MovingSprite::Update(ip, elapsedTime);
}

void WaterFall::Draw(IP& ip) {
    MovingSprite::Draw(ip);
}
