#include "FireWormBoss.h"
#include "Level.h"
#include "Character.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Renderer.h"
#include "IP.h"
#include "MathHelper.h"
#include "Map.h"
#include "Bullet.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"

FireWormBoss::FireWormBoss(IP& ip, Level& level)
    : Ennemy(ip, "fireWormBoss", sf::IntRect(0, 0, 43, 66), 4200, 1000, 500, level) {
    setPosition(sf::Vector2f(200, 279));
    SetFlying(true);
}

FireWormBoss::~FireWormBoss() {

}

void FireWormBoss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void FireWormBoss::Draw(IP& ip) {
    Ennemy::Draw(ip);
}

void FireWormBoss::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
}
