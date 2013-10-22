#include "Bullet.h"
#include "TextureLoader.h"
#include "IP.h"
#include "Level.h"
#include "Renderer.h"
#include "Map.h"
#include "Spawner.h"
#include "Character.h"
#include "ParticleManager.h"
#include "GameEntity.h"
#include "EntityManager.h"
#include "Ennemy.h"
#include "MathHelper.h"

Bullet::Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, int damage, float knockBack, bool animated, bool ennemy, bool gravity, bool instantDie, bool sticky)
    : MovingSprite(ip, name, hitbox, animated) {
    setPosition(position);
    SetVel(vel);
    _alive = true;
    _dying = false;
    _ennemy = ennemy;
    _gravity = gravity;
    _damage = damage;
    _instantDie = instantDie;
    _sticky = sticky;
    _inWater = false;
    _knockBack = knockBack;
}

Bullet::~Bullet() {

}

void Bullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    _inWater = IsInWater(level);

    if(_gravity && !_inWater) {
        Accelerate(sf::Vector2f(0, 0.001), eTime);
    }

    if((level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM) || level.GetSpawner().IsOnGround(*this)) && _gravity) {
        Accelerate(sf::Vector2f(-0.01*GetVel().x, 0), eTime);
    } else {
        //Accelerate(sf::Vector2f(-0.0003*GetVel().x, 0), eTime);
    }

    if(_inWater) {
        Accelerate(sf::Vector2f(-0.004*GetVel().x, -0.004*GetVel().y), eTime);
    }

    if(_dying) {
        float deadTime = _deadTimer.getElapsedTime().asMilliseconds();
        setColor(sf::Color(getColor().r, getColor().g, getColor().b, 255-deadTime/1000.f*255));
        if(deadTime > 1000 || _instantDie) {
            _alive = false;
        }
    }

    if(!_dying) {
        MovingSprite::Update(ip, eTime);
        TestCollisions(ip, eTime, level, GetVel()*eTime);
        WaterCollision(level, GetVel()*eTime, pManager, ip);
        if(_ennemy) {
            if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
                Impact((GameEntity&)(character), ip, pManager, sf::Color(255, 0, 0), eManager, level);
            }
        } else {
            for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
                Ennemy *e = eManager.GetEnnemy(i);
                if(e->GetGlobalHitbox().intersects(GetGlobalHitbox())) {
                    Impact((GameEntity&)(*e), ip, pManager, sf::Color(255, 255, 0), eManager, level);
                }
            }
        }

        if(_timer.getElapsedTime().asSeconds() > 4) {
            _dying = true;
            _deadTimer.restart();
        }
    }
}

void Bullet::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}

void Bullet::TestCollisions(IP& ip, float eTime, Level& level, sf::Vector2f delta) {
    if(_dying) {
        return;
    }
    if(abs(delta.x > 2.f) || abs(delta.y) > 2.f) {
        for(int i=0 ; i<2 ; i++) {
            TestCollisions(ip, eTime, level, delta/2.f);
        }
        return;
    }

    if(level.GetMap().IsCollided(*this, GetGlobalUpperLeftPos()+delta, Map::WALL) || level.GetSpawner().IsCollided(*this, GetGlobalUpperLeftPos()+delta)) {
        _dying = true;
        _deadTimer.restart();
        setPosition(getPosition() + delta);
    }
    if(GetVel().y >= 0 && !((int)(GetGlobalHitbox().top + GetGlobalHitbox().height + delta.y)%16 > 3) && _gravity) {
        if(level.GetMap().IsOnTileType(*this, GetGlobalUpperLeftPos()+delta, Map::PLATFORM)) {
            _dying = true;
            _deadTimer.restart();
            setPosition(getPosition() + delta);
        }
    }
}

void Bullet::Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color, EntityManager& eManager, Level& level) {
    _dying = true;
    _instantDie = true;
    _deadTimer.restart();
    entity.Damage(_damage, ip, pManager, color, getPosition(), GetVel(), eManager, level);
    entity.SetVel(entity.GetVel() + GetVel()/MathHelper::GetVecLength(GetVel())*_knockBack);
}

bool Bullet::IsAlive() const {
    return _alive;
}

bool Bullet::IsDying() const {
    return _dying;
}
