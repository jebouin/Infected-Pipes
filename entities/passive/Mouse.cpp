#include "Mouse.h"
#include "IP.h"
#include "Level.h"
#include "Map.h"
#include "Spawner.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "Renderer.h"
#include "WaterField.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"

Mouse::Mouse(IP& ip)
    : GameEntity(ip, "mouse", sf::IntRect(0, 2, 6, 2), 42) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("idle", Animation(1, 100, sf::Vector2i(0, 0), sf::Vector2i(6, 5), true));
    t.AddAnimation("walking", Animation(4, 100, sf::Vector2i(0, 5), sf::Vector2i(6, 5), true));
    t.SetAnimation("walking");

    SetInvincible(true);
    SetSpeed(MathHelper::RandFloat(0.0008f, 0.0012));
    SetJumpPower(0.1f);
    SetWeight(0);
    _direction = rand()%2==0 ? true : false;
    _curAction = rand()%2==0 ? true : false;
    NewAction();
}

Mouse::~Mouse() {

}

void Mouse::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager) {
    Map& map(level.GetMap());
    Spawner& spawner(level.GetSpawner());

    GameEntity::Update(ip, eTime, level, eManager, pManager);

    if(_curAction) {
        if(_direction) {
            GoRight(eTime);
        } else {
            GoLeft(eTime);
        }

        sf::Vector2i tilePos = sf::Vector2i(getPosition()/16.f);
        if(_direction) {
            if(map.GetTileType(tilePos+sf::Vector2i(1, 0), Map::FRONT)==Map::WALL
               || map.GetTileType(tilePos+sf::Vector2i(1, 1), Map::FRONT)==Map::VOID
               || spawner.IsCollided(*this, GetLocalUpperLeftPos()+sf::Vector2f(2, 0))) {
                if(int(getPosition().x)%16 > 10) {
                    _direction = !_direction;
                }
            }
        } else {
            if(map.GetTileType(tilePos+sf::Vector2i(-1, 0), Map::FRONT)==Map::WALL
               || map.GetTileType(tilePos+sf::Vector2i(-1, 1), Map::FRONT)==Map::VOID
               || spawner.IsCollided(*this, GetLocalUpperLeftPos()+sf::Vector2f(-2, 0))) {
                if(int(getPosition().x)%16 < 6) {
                    _direction = !_direction;
                }
            }
        }
    }

    if(_actionTimer.getElapsedTime().asMilliseconds() >= _actionTime) {
        NewAction();
    }
}

void Mouse::Draw(IP& ip) {
    GameEntity::Draw(ip);
}

void Mouse::NewAction() {
    _actionTimer.restart();
    if(_curAction) {
        _actionTime = MathHelper::RandFloat(1000, 2000);
        GetAnims().SetAnimation("idle");
    } else {
        _actionTime = MathHelper::RandFloat(1500, 3000);
        GetAnims().SetAnimation("walking");
    }
    _curAction = !_curAction;
}
