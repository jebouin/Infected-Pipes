#include "WormBoss.h"
#include "Level.h"
#include "Character.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "Renderer.h"
#include "IP.h"
#include "MathHelper.h"
#include "Map.h"
#include "Bullet.h"
#include "Particle.h"
#include "AnimationTable.h"
#include "Animation.h"

WormBoss::WormBoss(IP& ip, Level& level)
        : Ennemy(ip, "wormBossHead", sf::IntRect(0, 0, 21, 21), 800, 100, 50, level) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("nomnomnom", Animation(4, 80, sf::Vector2i(0, 0), sf::Vector2i(22, 22), true));
    t.SetAnimation("nomnomnom");
    _nbPartsExploded = 0;
    setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(level.GetMap().GetSize().x*8, level.GetMap().GetSize().y*16))));
    SetPhysics(false);
    for(int i=0 ; i<12 ; i++) {
        MovingSprite* p = new MovingSprite(ip, "wormBossBody", sf::IntRect(0, 0, 22, 21), true);
        p->setPosition(getPosition() + sf::Vector2f(0, (i+1)*(getGlobalBounds().height-1)));
        _parts.push_back(p);
    }
    ChangeState(INGROUND);
}

WormBoss::~WormBoss() {

}

void WormBoss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Map m(level.GetMap());
    if(_curState == DYING) {
        if(_explodeTimer.getElapsedTime().asMilliseconds() >= 50) {
            ExplodeParticles(ip, pManager, _parts[_nbPartsExploded]->getPosition());
            _nbPartsExploded++;
            if(_nbPartsExploded >= _parts.size()) {
                SetAlive(false);
            }
            _explodeTimer.restart();
        }
        return;
    }

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);
    //part and bullet/character collision
    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
        if(_attackTimer.getElapsedTime().asMilliseconds() >= 400) {
            character.Damage(MathHelper::RandInt(30, 35), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), sf::Vector2f(0, -1) * MathHelper::RandFloat(.4, .6), eManager, level);
            _attackTimer.restart();
        }
        sf::Vector2f forceDir(MathHelper::Normalize(character.getPosition()-getPosition()));
        character.Accelerate(forceDir*0.01f, eTime);
        //character.setPosition(getPosition() + forceDir*1.5f*20.f);
    }
    for(int i=0 ; i<_parts.size() ; i++) {
        MovingSprite* p(_parts[i]);

        if(p->GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
            if(_attackTimer.getElapsedTime().asMilliseconds() >= 400) {
                character.Damage(MathHelper::RandInt(18, 22), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), sf::Vector2f(character.GetVel().x, 0)/2.f, eManager, level);
                _attackTimer.restart();
            }
            sf::Vector2f forceDir(MathHelper::Normalize(character.getPosition()-p->getPosition()));
            character.Accelerate(forceDir*0.01f, eTime);
            //character.setPosition(p->getPosition() + forceDir*1.5f*20.f);
        }

        for(int i=0 ; i<bManager.GetCount() ; i++) {
            Bullet* b(bManager.GetBullet(i));
            if(b->GetGlobalHitbox().intersects(p->GetGlobalHitbox())) {
                b->Die(ip, pManager, eManager, level);
            }
        }
    }

    //set parts position if out of the ground
    if(_curState == IDLE || _curState == GOINGDOWN || _curState == GOINGUP) {
        for(int i=0 ; i<_parts.size() ; i++) {
            MovingSprite* p(_parts[i]);
            float xPos = sin(_timer.getElapsedTime().asSeconds()*4.f + float(i%3)*2.f/3.f*3.14159)*8.f*(float(i)/5.f);
            float yPos = (i+1)*(getGlobalBounds().height-1);
            p->setPosition(sf::Vector2f(getPosition().x+xPos, getPosition().y+yPos));
        }
    }
    if(_curState == INGROUND || _curState == PREPARING) {
        for(int i=0 ; i<_parts.size() ; i++) {
            MovingSprite* p(_parts[i]);
            float yPos = (i+1)*(getGlobalBounds().height-1);
            p->setPosition(sf::Vector2f(getPosition().x, getPosition().y+yPos));
        }
    }

    if(_curState == JUMPING) {
        static float gravity(0.0006f);
        static float tension(0.002f);
        Accelerate(sf::Vector2f(MathHelper::Normalize(character.getPosition()-getPosition()).x*.004f, 0), eTime);
        Accelerate(sf::Vector2f(-GetVel().x*0.01f, gravity), eTime);
        for(int i=0 ; i<_parts.size() ; i++) {
            MovingSprite* p(_parts[i]);
            p->Accelerate(-p->GetVel()*0.01f, eTime);
            if(m.IsCollided(*p, Map::WALL) && rand()%2==0 && MathHelper::GetVecLength(p->GetVel())>.1 && m.IsCollided(*p, Map::VOID)) {
                int type = rand()%2;
                pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                                  sf::Vector2f(p->getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), p->getPosition().y-10),
                                                  MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-20, 20) + MathHelper::Vec2Ang(-p->GetVel())-90)) * MathHelper::RandFloat(.3, .5),
                                                  MathHelper::RandFloat(-1., 1.),
                                                  MathHelper::RandFloat(600, 1400),
                                                  sf::Vector2f(1, 1),
                                                  sf::Vector2f(1, 1),
                                                  255,
                                                  0,
                                                  true,
                                                  true,
                                                  false,
                                                  type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3), false));
            }
        }
        setRotation(90 + MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));

        float maxL = 20.f;
        MovingSprite* p(_parts[0]);
        float curL = MathHelper::GetVecLength(p->getPosition()-getPosition());
        if(curL > maxL) {
            sf::Vector2f forceDir(MathHelper::Normalize(getPosition()-p->getPosition()));
            p->setPosition(getPosition() - forceDir*maxL);
            //p->Accelerate(forceDir*tension, eTime);
        }

        for(int i=1 ; i<_parts.size() ; i++) {
            MovingSprite* p(_parts[i]);
            MovingSprite* pp(_parts[i-1]);
            float curL = MathHelper::GetVecLength(p->getPosition()-pp->getPosition());
            if(curL > maxL) {
                sf::Vector2f forceDir(MathHelper::Normalize(pp->getPosition()-p->getPosition()));
                p->setPosition(pp->getPosition() - forceDir*maxL);
                //p->Accelerate(forceDir*tension, eTime);
            }
        }

        //if all parts are in the ground and of course moving down, stop jumping
        if(GetVel().y > 0) {
            bool finished = true;
            for(int i=0 ; i<_parts.size() ; i++) {
                MovingSprite* p(_parts[i]);
                if(m.IsCollided(*p, Map::VOID)) {
                    finished = false;
                }
            }
            if(finished) {
                ChangeState(INGROUND);
                SetVel(sf::Vector2f(0, 0));
                setPosition(sf::Vector2f(getPosition().x, getPosition().y + (-(GetGlobalHitbox().top) + m.GetSize().y*16)));
                setRotation(0);
            }
        }
    }

    if(_curState == GOINGUP) {
        MovingSprite* p(_parts[4]);
        if(p->GetGlobalHitbox().top+p->GetGlobalHitbox().height <= m.GetSize().y*16-16) {
            ChangeState(IDLE);
            SetVel(sf::Vector2f(0, 0));
            setPosition(sf::Vector2f(getPosition().x, getPosition().y + (-(p->GetGlobalHitbox().top+p->GetGlobalHitbox().height) + m.GetSize().y*16-16)));
        }
    }

    if(_curState == GOINGDOWN) {
        if(GetGlobalHitbox().top >= m.GetSize().y*16) {
            ChangeState(INGROUND);
            SetVel(sf::Vector2f(0, 0));
            setPosition(sf::Vector2f(getPosition().x, getPosition().y + (-(GetGlobalHitbox().top) + m.GetSize().y*16)));
        }
    }

    if(_curState == PREPARING || _curState == GOINGUP || _curState == GOINGDOWN) {
        if(_particleTimer.getElapsedTime().asMilliseconds() >= 100) {
            _particleTimer.restart();
            for(int i=0 ; i<3 ; i++) {
                pManager.AddParticle(new Particle(ip, "smokeParticle",
                                                  sf::Vector2f(getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), m.GetSize().y*16-16),
                                                  sf::Vector2f(0., 0.),
                                                  MathHelper::RandFloat(-.5, .5),
                                                  MathHelper::RandFloat(200, 400),
                                                  sf::Vector2f(.5, .5),
                                                  sf::Vector2f(2., 2.),
                                                  128,
                                                  0,
                                                  false,
                                                  false,
                                                  false,
                                                  sf::IntRect(2, 2, 3, 3), false));
            }
            if(_curState == GOINGUP || _curState == GOINGDOWN) {
                for(int i=0 ; i<3 ; i++) {
                    int type = rand()%2;
                    pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                                      sf::Vector2f(getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), m.GetSize().y*16-20),
                                                      MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.3, .5),
                                                      MathHelper::RandFloat(-1., 1.),
                                                      MathHelper::RandFloat(600, 1400),
                                                      sf::Vector2f(1, 1),
                                                      sf::Vector2f(1, 1),
                                                      255,
                                                      0,
                                                      true,
                                                      true,
                                                      false,
                                                      type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3), false));
                }
            }
        }
    }

    //Update state
    if(_stateTimer.getElapsedTime().asMilliseconds() >= _nextStateTime) {
        if(_curState == IDLE) {
            ChangeState(GOINGDOWN);
            SetVel(sf::Vector2f(0, .25));
        } else if(_curState == INGROUND) {
            ChangeState(PREPARING);
            float newX = MathHelper::RandFloat(32+GetGlobalHitbox().width, m.GetSize().x*16.f-32-GetGlobalHitbox().width);
            if(rand()%2) {
                newX = character.getPosition().x;
            }
            setPosition(sf::Vector2f(newX, getPosition().y));
        } else if(_curState == PREPARING) {
            if(rand()%2) {
                ChangeState(JUMPING);
                SetVel(sf::Vector2f((character.getPosition().x-getPosition().x)*.0006f, -0.5));
                for(int i=0 ; i<8 ; i++) {
                    int type = rand()%2;
                    pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                                      sf::Vector2f(getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), m.GetSize().y*16-20),
                                                      MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.3, .5),
                                                      MathHelper::RandFloat(-1., 1.),
                                                      MathHelper::RandFloat(600, 1400),
                                                      sf::Vector2f(1, 1),
                                                      sf::Vector2f(1, 1),
                                                      255,
                                                      0,
                                                      true,
                                                      true,
                                                      false,
                                                      type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3), false));
                }
            } else {
                ChangeState(GOINGUP);
                SetVel(sf::Vector2f(0, -.4));
            }
        }
    }

    /*static std::string stateS[7] = {"IDLE", "PREPARING", "JUMPING", "GOINGUP", "GOINGDOWN", "INGROUND", "DYING"};
    cout << stateS[_curState] << endl;*/
}

void WormBoss::Draw(IP& ip) {
    if(_curState != DYING) {
        Ennemy::Draw(ip);
    }
    for(int i=0 ; i<_parts.size() ; i++) {
        if(_curState != DYING || i>=_nbPartsExploded) {
            ip._renderer->Draw(*_parts[i]);
        }
    }
}

void WormBoss::ChangeState(State state) {
    _curState = state;
    _stateTimer.restart();
    switch(state) {
    case IDLE:
        _nextStateTime = MathHelper::RandInt(2000, 4000);
        break;
    case PREPARING:
        _nextStateTime = MathHelper::RandInt(300, 500);
        break;
    case JUMPING:
        _nextStateTime = 42000000; //transition
        break;
    case GOINGUP:
        _nextStateTime = 42000000;
        break;
    case GOINGDOWN:
        _nextStateTime = 42000000;
        break;
    case INGROUND:
        _nextStateTime = MathHelper::RandInt(700, 1000);
        break;
    case DYING:
        _nextStateTime = 42000000;
        break;
    }
}

void WormBoss::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);
    ExplodeParticles(ip, pManager, getPosition());
    SetAlive(true);
    SetInvincible(true);
    ChangeState(DYING);
    _explodeTimer.restart();
}

void WormBoss::ExplodeParticles(IP& ip, ParticleManager& pManager, sf::Vector2f pos) {
    for(int i=0 ; i<21 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                          pos+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 11.),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.1, .35),
                                          MathHelper::RandFloat(-1., 1.),
                                          MathHelper::RandFloat(1000, 2000),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3), false));
    }
    for(int i=0 ; i<10 ; i++) {
        int type = rand()%2;
        pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle3" : "rockParticle4",
                                          pos+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 11.),
                                          MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.2, .8),
                                          MathHelper::RandFloat(-1., 1.),
                                          MathHelper::RandFloat(1000, 2000),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          true,
                                          true,
                                          false,
                                          type==0 ? sf::IntRect(2, 2, 5, 5) : sf::IntRect(2, 2, 9, 7), false));
    }
    for(int i=0 ; i<10 ; i++) {
        pManager.AddParticle(new Particle(ip, "smokeParticle",
                                          pos+MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(0., 20.),
                                          sf::Vector2f(0., 0.),
                                          MathHelper::RandFloat(-.5, .5),
                                          MathHelper::RandFloat(200, 400),
                                          sf::Vector2f(.5, .5),
                                          sf::Vector2f(2., 2.),
                                          128,
                                          0,
                                          false,
                                          false,
                                          false,
                                          sf::IntRect(2, 2, 3, 3), false));
    }
}
