#include "Bullet.h"
#include "ResourceLoader.h"
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

Bullet::Bullet(IP& ip, std::string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, int damage, float knockBack, bool animated, bool ennemy, bool gravity, bool instantDie, bool sticky, bool dieOnWall, bool bounce)
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
    _dieOnWall = dieOnWall;
    _bounce = bounce;
    _collisionWithEnnemies = true;
    _trail.setPrimitiveType(sf::Lines);
    _trail.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 0)));
    _trail.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 0)));
}

Bullet::~Bullet() {

}

void Bullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    _prevPos = getPosition();
    _inWater = IsInWater(level);

    if(_gravity && !_inWater) {
        Accelerate(sf::Vector2f(0, 0.001), eTime);
    }

    if((level.GetMap().IsOnTileType(*this, Map::WALL) || level.GetMap().IsOnTileType(*this, Map::PLATFORM) || level.GetSpawner().IsOnGround(*this)) && _gravity) {
        Accelerate(sf::Vector2f(-0.01*GetVel().x, 0), eTime);
    } else {
        //Accelerate(sf::Vector2f(-0.0003*GetVel().x, 0), eTime);
    }

    if(_inWater && GetCollidesWithWater()) {
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
        if(!_bounce) {
            MovingSprite::Update(ip, eTime);
        }
        TestCollisions(ip, eTime, level, GetVel()*eTime);
        WaterCollision(level, GetVel()*eTime, pManager, ip);
        if(_collisionWithEnnemies) {
            if(_ennemy) {
                if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
                    Impact((GameEntity&)(character), ip, pManager, sf::Color(255, 0, 0), eManager, level);
                }
            } else {
                sf::Vector2f dir = MathHelper::Normalize(getPosition() - _prevPos);
                float l = MathHelper::GetVecLength(getPosition() - _prevPos);
                //cout << l << endl;
                _trail.clear();
                for(float j=0 ; j<l ; j+=4) {
                    sf::Vector2f curPos(_prevPos + j*dir);
                    _trail.append(sf::Vertex(curPos, sf::Color(255, 255, 0)));
                    for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
                        Ennemy *e = eManager.GetEnnemy(i);
                        if(sf::FloatRect(sf::Vector2f(curPos), sf::Vector2f(GetGlobalHitbox().width, GetGlobalHitbox().height)).intersects(e->GetGlobalHitbox())) {
                            Impact((GameEntity&)(*e), ip, pManager, sf::Color(255, 255, 0), eManager, level);
                            break;
                        }
                    }
                    if(_dying) {
                        break;
                    }
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
    //ip._renderer->Draw(*this);
    MovingSprite::Draw(ip);
    ip._renderer->Draw(_trail);
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

    if(_bounce) {
        static float p = .01f;
        if(!TryMove(delta, level)) {
            for(float i=p ; i<MathHelper::ABS(delta.x)-p ; i+=p) {
                if(!TryMove(sf::Vector2f(MathHelper::SGN(delta.x)/(1./p), 0), level)) {
                    SetVel(sf::Vector2f(-GetVel().x*.5, GetVel().y));
                    //SetRotVel(GetRotVel()/2.f);
                    break;
                }
            }
            for(float i=p ; i<MathHelper::ABS(delta.y)-p ; i+=p) {
                if(!TryMove(sf::Vector2f(0, MathHelper::SGN(delta.y)/(1./p)), level)) {
                    SetVel(sf::Vector2f(GetVel().x, -GetVel().y*.5));
                    //SetRotVel(GetRotVel()/2.f);
                    break;
                }
            }

            if(_dieOnWall) {
                _dying = true;
                _deadTimer.restart();
            }
        } else {

        }
    } else {
        if(level.GetMap().IsCollided(*this, GetGlobalUpperLeftPos()+delta, Map::WALL) || level.GetSpawner().IsCollided(*this, GetGlobalUpperLeftPos()+delta)) {
            if(_dieOnWall) {
                _dying = true;
                _deadTimer.restart();
                //setPosition(getPosition() + delta);
            }
        }
    }
}

void Bullet::Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color, EntityManager& eManager, Level& level) {
    if(!entity.IsAlive()) {
        return;
    }
    _dying = true;
    _instantDie = true;
    _deadTimer.restart();
    entity.Damage(_damage, ip, pManager, color, getPosition(), GetVel(), eManager, level);
    if(entity.HasPhysics()) {
        entity.SetVel(entity.GetVel() + GetVel()/MathHelper::GetVecLength(GetVel())*_knockBack);
    }
}

bool Bullet::IsAlive() const {
    return _alive;
}

bool Bullet::IsDying() const {
    return _dying;
}

bool Bullet::CollisionWithEnnemies() const {
    return _collisionWithEnnemies;
}

void Bullet::SetCollisionWithEnnemies(bool c) {
    _collisionWithEnnemies = c;
}

bool Bullet::Die() {
    if(!_dying) {
        _dying = true;
        _deadTimer.restart();
    }
}
