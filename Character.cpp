#include "Character.h"
#include "IP.h"

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(2, 0, 7, 26)) {
    SetWeight(0.2f);
}

Character::~Character() {

}

void Character::Update(IP& ip, float eTime, Map& map, EntityManager& eManager) {
    GameEntity::Update(ip, eTime, map, eManager);
}
