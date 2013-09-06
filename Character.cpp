#include "Character.h"
#include "IP.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "EntityManager.h"

Character::Character(IP& ip) : GameEntity(ip, "character", sf::IntRect(2, 0, 7, 26), 10) {
    SetWeight(0.5f);
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", new Animation(1, 1000, sf::Vector2i(0, 0), sf::Vector2i(22, 26), true));
    t.AddAnimation("attack", new Animation(1, 200, sf::Vector2i(0, 26), sf::Vector2i(22, 26), false));
    t.SetAnimation("idle");
}

Character::~Character() {

}

void Character::Update(IP& ip, float eTime, Map& map, EntityManager& eManager) {
    GameEntity::Update(ip, eTime, map, eManager);

    if(GetAnims().GetAnimationName()=="idle") {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            GetAnims().SetAnimation("attack");
            for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
                Hit((GameEntity*)eManager.GetEnnemy(i));
            }
        }
    } else {
        if(GetAnims().GetAnimation().IsFinished()) {
            GetAnims().SetAnimation("idle");
        }
    }
}
