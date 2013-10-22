#include "Arrow.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

Arrow::Arrow(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "arrow", sf::IntRect(0, 1, 13, 3), position, vel, 120, .2, true, ennemy, true, false, true) {

}

Arrow::~Arrow() {

}

void Arrow::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    if(!IsDying()) {
        setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
        SetHitbox(sf::IntRect(0, 0, getGlobalBounds().width, getGlobalBounds().height));
    }
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
}

void Arrow::Draw(IP& ip) {
    Bullet::Draw(ip);
}
