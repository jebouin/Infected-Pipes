#include "Boss.h"
#include "Level.h"
#include "Character.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Renderer.h"
#include "MovingSprite.h"

Boss::Boss(IP& ip, string name, sf::IntRect hitbox, int hp, int xp, int incDifficulty, Level& level)
    : Ennemy(ip, name, hitbox, hp, xp, incDifficulty, level) {

}

Boss::~Boss() {
    ClearParts();
}

void Boss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
    for(int i=0 ; i<GetNbParts() ; i++) {
        _parts[i]->Update(ip, eTime);
    }
}

void Boss::Draw(IP& ip) {
    Ennemy::Draw(ip);
    for(int i=0 ; i<GetNbParts() ; i++) {
        _parts[i]->Draw(ip);
    }
}

void Boss::AddPart(MovingSprite* part) {
    _parts.push_back(part);
}

void Boss::ClearParts() {
    for(int i=0 ; i<GetNbParts() ; i++) {
        delete _parts[i];
        _parts[i] = 0;
    }
    _parts.clear();
}

int Boss::GetNbParts() {
    return _parts.size();
}

MovingSprite* Boss::GetPart(int id) {
    if(id<0 || id>=GetNbParts()) {
        return 0;
    }
    return _parts[id];
}
