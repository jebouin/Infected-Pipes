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
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"

Ennemy::Ennemy(IP& ip, std::string name, sf::IntRect hitbox, int hp, int xp, int incDifficulty, Level& level) : GameEntity(ip, name, hitbox, hp), _level(level) {
    SetSpeed(MathHelper::RandFloat(0.0005, 0.001));
    SetJumpPower(0.6);
    _inPipe = true;
    _xp = xp;
    _incDifficulty = incDifficulty;
    _character = 0;
    setColor(sf::Color(255, 255, 255, 255));
}

Ennemy::~Ennemy() {
    _level.SetDifficulty(_level.GetDifficulty() + _incDifficulty);
}

void Ennemy::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    if(_character == 0) {
        _character = &character;
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

void Ennemy::Draw(IP& ip) {
    GameEntity::Draw(ip);
}

int Ennemy::GetXP() {
    return _xp;
}

int Ennemy::GetIncDifficulty() {
    return _incDifficulty;
}

void Ennemy::Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level) {
    GameEntity::Damage(dmg, ip, pManager, color, pos, dir, eManager, level);
    Particle *p = new Particle(ip, "littleImpact",
                                  pos,
                                  sf::Vector2f(0., 0.),
                                  0,
                                  150,
                                  sf::Vector2f(1, 1),
                                  sf::Vector2f(1, 1),
                                  255,
                                  255,
                                  false,
                                  false,
                                  true,
                                  sf::IntRect(2, 2, 4, 4), false);
    p->GetAnims().AddAnimation("boom", new Animation(3, 50, sf::Vector2i(0, 0), sf::Vector2i(8, 8), false));
    p->GetAnims().SetAnimation("boom");
    pManager.AddParticle(p);
}

void Ennemy::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    GameEntity::Die(ip, pManager, eManager, level);
    _character->EarnXP(_xp);
}
