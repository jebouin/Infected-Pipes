#include "WormBoss.h"
#include "Level.h"
#include "Character.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Renderer.h"

WormBoss::WormBoss(IP& ip, Level& level) : Boss(ip, "wormBossBody", sf:IntRect(0, 0, 22, 22), 100, 100, 50, level) {

}

WormBoss::~WormBoss() {
    ClearParts();
}

void WormBoss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Boss::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void WormBoss::Draw(IP& ip) {
    Boss::Draw(ip);
}
