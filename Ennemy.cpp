#include "Ennemy.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"

Ennemy::Ennemy(IP& ip) : GameEntity(ip, "zombie", sf::IntRect(1, 0, 5, 20), 10) {
    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
    SetJumpPower(0.6);
    _inPipe = true;
}

Ennemy::~Ennemy() {

}

void Ennemy::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager) {
    if(getPosition().x < character.getPosition().x) {
        GoRight(eTime);
    } else if(getPosition().x > character.getPosition().x) {
        GoLeft(eTime);
    }

    if(/*MathHelper::ABS(GetVel().x) < 0.01 && MathHelper::ABS(getPosition().x-character.getPosition().x) > 16*/0) {
        Jump(level);
    }

    if(_inPipe) {
        GameEntity::Update(ip, eTime);
        if(!level.GetSpawner().IsCollided(*this)) {
            _inPipe = false;
        }
    } else {
        GameEntity::Update(ip, eTime, level, eManager, pManager);
    }
}
