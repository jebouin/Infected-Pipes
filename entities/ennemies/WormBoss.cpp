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

WormBoss::WormBoss(IP& ip, Level& level)
        : Boss(ip, "wormBossHead", sf::IntRect(0, 0, 21, 21), 1000, 100, 50, level) {
    setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(level.GetMap().GetSize().x*8, level.GetMap().GetSize().y*16))));
    SetPhysics(false);
    for(int i=0 ; i<5 ; i++) {
        MovingSprite* p = new MovingSprite(ip, "wormBossBody", sf::IntRect(0, 0, 22, 21), true);
        p->setPosition(getPosition() + sf::Vector2f(0, (i+1)*(getGlobalBounds().height-1)));
        AddPart(p);
    }
    ChangeState(INGROUND);
}

WormBoss::~WormBoss() {

}

void WormBoss::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    Map m(level.GetMap());
    Boss::Update(ip, eTime, level, character, eManager, pManager, bManager);
    //part and bullet/character collision
    for(int i=0 ; i<GetNbParts() ; i++) {
        MovingSprite* p(GetPart(i));

        if(p->GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
            character.Accelerate(sf::Vector2f(0.07*MathHelper::SGN(character.getPosition().x-p->getPosition().x), 0), eTime);
            character.Damage(MathHelper::RandInt(18, 22), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), sf::Vector2f(character.GetVel().x, 0)/2.f, eManager, level);
        }

        for(int i=0 ; i<bManager.GetCount() ; i++) {
            Bullet* b(bManager.GetBullet(i));
            if(b->GetGlobalHitbox().intersects(p->GetGlobalHitbox())) {
                b->Die();
            }
        }
    }

    //set parts position if out of the ground
    if(_curState == IDLE || _curState == GOINGDOWN || _curState == GOINGUP) {
        for(int i=0 ; i<GetNbParts() ; i++) {
            MovingSprite* p(GetPart(i));
            float xPos = sin(_timer.getElapsedTime().asSeconds()*4.f + float(i%3)*2.f/3.f*3.14159)*8.f*(1.f-float(i)/float(GetNbParts()));
            float yPos = (i+1)*(getGlobalBounds().height-1);
            p->setPosition(sf::Vector2f(getPosition().x+xPos, getPosition().y+yPos));
        }
    }

    if(_curState == GOINGUP) {
        MovingSprite* p(GetPart(GetNbParts()-1));
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
                                                  sf::IntRect(2, 2, 3, 3)));
            }
            if(_curState == GOINGUP || _curState == GOINGDOWN) {
                pManager.AddParticle(new Particle(ip, "rockParticle",
                                                  sf::Vector2f(getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), m.GetSize().y*16-24),
                                                  MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-120, -60))) * MathHelper::RandFloat(.3, .5),
                                                  MathHelper::RandFloat(-.5, .5),
                                                  MathHelper::RandFloat(400, 700),
                                                  sf::Vector2f(1., 1.),
                                                  sf::Vector2f(1., 1.),
                                                  255,
                                                  0,
                                                  true,
                                                  true,
                                                  false,
                                                  sf::IntRect(1, 1, 4, 3)));
                int type = rand()%2;
                pManager.AddParticle(new Particle(ip, type==0 ? "rockParticle" : "rockParticle2",
                                                  sf::Vector2f(getPosition().x + MathHelper::RandFloat(-GetGlobalHitbox().width/2.f, GetGlobalHitbox().width/2.f), m.GetSize().y*16-24),
                                                  MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, 20))) * MathHelper::RandFloat(.3, .5),
                                                  MathHelper::RandFloat(-1., 1.),
                                                  MathHelper::RandFloat(600, 1400),
                                                  sf::Vector2f(1, 1),
                                                  sf::Vector2f(1, 1),
                                                  255,
                                                  0,
                                                  true,
                                                  true,
                                                  false,
                                                  type==0 ? sf::IntRect(1, 1, 4, 4) : sf::IntRect(1, 1, 5, 3)));
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
        } else if(_curState == PREPARING) {
            if(/*rand()%2*/0) {
                ChangeState(JUMPING);
            } else {
                ChangeState(GOINGUP);
                SetVel(sf::Vector2f(0, -.4));
            }
        }
    }

    static string stateS[6] = {"IDLE", "PREPARING", "JUMPING", "GOINGUP", "GOINGDOWN", "INGROUND"};
    cout << stateS[_curState] << endl;
}

void WormBoss::Draw(IP& ip) {
    Boss::Draw(ip);
}

void WormBoss::ChangeState(State state) {
    _curState = state;
    _stateTimer.restart();
    switch(state) {
    case IDLE:
        _nextStateTime = MathHelper::RandInt(2000, 4000);
        break;
    case PREPARING:
        _nextStateTime = MathHelper::RandInt(800, 1200);
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
        _nextStateTime = MathHelper::RandInt(1500, 2300);
        break;
    }
}
