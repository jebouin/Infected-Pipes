#include "Ennemy.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "BulletManager.h"

Ennemy::Ennemy(IP& ip, string name, sf::IntRect hitbox, int hp, int xp, int incDifficulty) : GameEntity(ip, name, hitbox, hp) {
    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
    SetJumpPower(0.6);
    _inPipe = true;
    _xp = xp;
    _incDifficulty = incDifficulty;
}

Ennemy::~Ennemy() {

}

void Ennemy::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    if(_inPipe) {
        GameEntity::Update(ip, eTime);
        if(!level.GetSpawner().IsCollided(*this)) {
            _inPipe = false;
        }
    } else {
        GameEntity::Update(ip, eTime, level, eManager, pManager);
    }
}

int Ennemy::GetXP() {
    return _xp;
}

int Ennemy::GetIncDifficulty() {
    return _incDifficulty;
}
