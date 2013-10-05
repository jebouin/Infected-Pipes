#include "Snail.h"
#include "IP.h"
#include "Map.h"
#include "Level.h"
#include "Character.h"
#include "MathHelper.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "BulletManager.h"
#include "LaserBullet.h"
#include "Renderer.h"

Snail::Snail(IP& ip) : Ennemy(ip, "snail", sf::IntRect(3, 1, 26, 20), 42, 8, 6) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("walk", new Animation(2, 200, sf::Vector2i(0, 0), sf::Vector2i(31, 21), true));
    t.AddAnimation("prepare", new Animation(1, 100, sf::Vector2i(0, 21), sf::Vector2i(31, 21), false));
    t.SetAnimation("walk");
    SetSpeed(MathHelper::RandFloat(0.0003, 0.0004));
    _preparing = false;
    _nextAttack = MathHelper::RandFloat(1000, 3000);

    _circle.setFillColor(sf::Color(0, 0, 0, 0));
    _circle.setOutlineColor(sf::Color(220, 200, 255));
    _circle.setOutlineThickness(1);
    _circle.setPointCount(42);
}

Snail::~Snail() {

}

void Snail::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    sf::FloatRect r(GetGlobalHitbox());
    sf::Vector2f c(MathHelper::GetCenter(r));
    sf::Vector2f cc(MathHelper::GetCenter(character.GetGlobalHitbox()));
    AnimationTable& t(GetAnims());
    float attackTime = _attackTimer.getElapsedTime().asMilliseconds();
    sf::Vector2f eyePos = GetUpperLeftPos() + sf::Vector2f(GetDir() ? GetAnims().GetAnimation().GetRect().width-1. : 0., 1.);

    if(!_preparing) {
        if(c.x < cc.x) {
            GoRight(eTime);
        } else if(c.x > cc.x) {
            GoLeft(eTime);
        }

        if(level.GetMap().IsOnTileType(*this, Map::PLATFORM)) {
            if(c.y - cc.y < -10.f) {
                PlatformDrop(level);
            }
        }

        if(attackTime >= _nextAttack) {
            _preparing = true;
            _attackTimer.restart();
            t.SetAnimation("prepare");
        }
    } else {
        if(attackTime >= 1000) {
            _preparing = false;
            _attackTimer.restart();
            t.SetAnimation("walk");
            _nextAttack = MathHelper::RandFloat(1000, 3000);

            //shoot
            bManager.AddBullet(new LaserBullet(ip,
                                              eyePos,
                                              -MathHelper::Normalize(eyePos - cc)*0.4f,
                                              true));
        }
        UpdateCircle(eyePos);
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
}

void Snail::Draw(IP& ip) {
    Ennemy::Draw(ip);
    if(_preparing) {
        ip._renderer->Draw(_circle);
    }
}

void Snail::UpdateCircle(sf::Vector2f eyePos) {
    float attackTime = _attackTimer.getElapsedTime().asMilliseconds();
    _circle.setOrigin(sf::Vector2f(_circle.getRadius(), _circle.getRadius()));
    _circle.setPosition(eyePos);
    float p = attackTime/1000.0;
    _circle.setRotation(p*360.f);
    sf::Color color = _circle.getOutlineColor();
    _circle.setRadius(20.0 - 1.0/p*20.0);
    _circle.setOutlineColor(sf::Color(color.r, color.g, color.b, p*255));
}
