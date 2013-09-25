#include "Bat.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"

Bat::Bat(IP& ip) : Ennemy(ip, "bat", sf::IntRect(3, 0, 13, 18), 20, 3, 3) {
    AnimationTable& t(GetAnims());

    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
}

Bat::~Bat() {

}

void Bat::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {


    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}
