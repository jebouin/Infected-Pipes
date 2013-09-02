#include "Ennemy.h"
#include "IP.h"
#include "Map.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"

Ennemy::Ennemy(IP& ip) : GameEntity(ip, "zombie", sf::IntRect(1, 0, 5, 20)) {
    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
    SetJumpPower(0.6);
}

Ennemy::~Ennemy() {

}

void Ennemy::Update(IP& ip, float eTime, Map& map, Character& character, EntityManager& eManager) {
    if(getPosition().x < character.getPosition().x) {
        GoRight(eTime);
    } else if(getPosition().x > character.getPosition().x) {
        GoLeft(eTime);
    }

    GameEntity::Update(ip, eTime, map, eManager);

    /*if(MathHelper::ABS(GetVel().x) < 0.01 && MathHelper::ABS(getPosition().x-character.getPosition().x) > 16) {
        Jump(map);
    }*/
}
