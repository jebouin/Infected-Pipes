#include "Arrow.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"

Arrow::Arrow(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "arrow", sf::IntRect(0, 1, 13, 3), position, vel, 42, true, ennemy, true) {

}

Arrow::~Arrow() {

}

void Arrow::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);
    setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
}

void Arrow::Draw(IP& ip) {
    Bullet::Draw(ip);
}
