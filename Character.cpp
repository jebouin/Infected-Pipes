#include "Character.h"
#include "IP.h"
#include "Animation.h"
#include "Ennemy.h"
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

void Character::Update(IP& ip, float eTime, Level& level, EntityManager& eManager) {
    GameEntity::Update(ip, eTime, level, eManager);

    if(GetAnims().GetAnimationName()=="idle") {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            GetAnims().SetAnimation("attack");
            for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
                sf::FloatRect attackRect;
                if(GetDir()) {
                    attackRect = sf::FloatRect(GetGlobalHitbox().left+GetGlobalHitbox().width, GetGlobalHitbox().top, 16, GetGlobalHitbox().height);
                } else {
                    attackRect = sf::FloatRect(GetGlobalHitbox().left-16, GetGlobalHitbox().top, 16, GetGlobalHitbox().height);
                }
                if(eManager.GetEnnemy(i)->GetGlobalHitbox().intersects(attackRect)) {
                    Hit((GameEntity*)eManager.GetEnnemy(i));
                }
            }
        }
    } else {
        if(GetAnims().GetAnimation().IsFinished()) {
            GetAnims().SetAnimation("idle");
        }
    }
}
