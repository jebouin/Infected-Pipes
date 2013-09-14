#include "Spiderock.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"

Spiderock::Spiderock(IP& ip) : Ennemy(ip, "spiderock", sf::IntRect(3, 0, 13, 18), 10) {

}

Spiderock::~Spiderock() {

}

void Spiderock::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager) {
    Ennemy::Update(ip, eTime, level, character, eManager, pManager);
}
