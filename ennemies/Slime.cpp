#include "Slime.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"

Slime::Slime(IP& ip, Level& level) : Ennemy(ip, "slime", sf::IntRect(1, 1, 18, 10), 7, 1, 1, level) {
    SetSpeed(0.002);
    SetJumpPower(.3);
    _nextJump = MathHelper::RandFloat(300, 500);
    SetAutoDir(false);
}

Slime::~Slime() {

}

void Slime::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    AnimationTable& t(GetAnims());

    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox()) && _attackTimer.getElapsedTime().asMilliseconds() > 800) {
        Hit(&character, ip, pManager, sf::Color(255, 0, 0), MathHelper::RandInt(3, 4), eManager, level);
        _attackTimer.restart();
    }

    if(_jumpTimer.getElapsedTime().asMilliseconds() >= _nextJump) {
        if(Jump(level)) {
            _jumpTimer.restart();
            _nextJump = MathHelper::RandFloat(300, 500);
        }
    }

    if(!level.GetMap().IsOnTileType(*this, Map::WALL) && !level.GetSpawner().IsOnGround(*this)) {
        if(c.x < cc.x) {
            GoRight(eTime);
        } else {
            GoLeft(eTime);
        }
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Slime::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    GameEntity::Die(ip, pManager, eManager, level);
    for(int i=0 ; i<4 ; i++) {
        pManager.AddParticle(new Particle(ip, "slimeParticle",
                                          getPosition()+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 6.),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.1, .35),
                                          0,
                                          MathHelper::RandFloat(400, 800),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(.0, .0),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          sf::IntRect(2, 2, 3, 3)));
    }
}
