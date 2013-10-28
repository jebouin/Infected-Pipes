#include "Skull.h"
#include "IP.h"
#include "Level.h"
#include "Map.h"
#include "Spawner.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "Renderer.h"
#include "WaterField.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"

Skull::Skull(IP& ip)
    : GameEntity(ip, "skull", sf::IntRect(1, 1, 12, 12), 42) {
    SetInvincible(true);
    SetWeight(0.1);
}

Skull::~Skull() {

}

void Skull::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager) {
    GameEntity::Update(ip, eTime, level, eManager, pManager);
}

void Skull::Draw(IP& ip) {
    GameEntity::Draw(ip);
}
