#include "Jellyfish.h"
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
#include "WaterField.h"
#include "Missile.h"
#include "Renderer.h"

Jellyfish::Jellyfish(IP& ip, Level& level)
    : Ennemy(ip, "jellyfish", sf::IntRect(5, 0, 13, 11), 200, 30, 40, level) {
    AnimationTable& anims(GetAnims());
    SetWaterFriction(.5);
    _moveTime = MathHelper::RandFloat(600, 800);

    _initTentacles = false;
}

Jellyfish::~Jellyfish() {

}

void Jellyfish::Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    if(!_initTentacles) {
        _tentaclesLines.setPrimitiveType(sf::Lines);
        static const int tentaclesLength = 240;
        static const int nbTentacles = 8;
        _tentaclesMovement = vector<float>(nbTentacles);
        for(int i=0 ; i<nbTentacles ; i++) {
            _tentacles.push_back(vector<TentaclePoint>());
            _tentaclesMovement[i] = MathHelper::RandFloat(0, 1);
            for(int j=0 ; j<tentaclesLength ; j++) {
                float intX = float(i)/float(nbTentacles-1);
                float offY = sin(intX*PI)*5;
                sf::Vector2f pos = sf::Vector2f(getGlobalBounds().left+getGlobalBounds().width*intX, getGlobalBounds().top+getGlobalBounds().height) + sf::Vector2f(0, -offY-1);
                _tentacles[i].push_back({pos, sf::Vector2f(0, 0)});
                if(j<tentaclesLength-1) {
                    int b(pow(1.f-(float(j)/float(tentaclesLength)), 2) * 255);
                    for(int k=0 ; k<2 ; k++) {
                        _tentaclesLines.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(106, 161, 183, b)));
                    }
                }
            }
        }
        _initTentacles = true;
    }

    AnimationTable& anims(GetAnims());
    sf::Vector2f dirToPlayer = MathHelper::Normalize(character.getPosition() - getPosition());
    if(GetGlobalHitbox().intersects(character.GetGlobalHitbox())) {
        if(_attackTimer.getElapsedTime().asMilliseconds() >= 800) {
            character.Damage(MathHelper::RandInt(30, 35), ip, pManager, sf::Color(255, 0, 0), character.getPosition(), dirToPlayer*MathHelper::RandFloat(.1, .2), eManager, level);
            _attackTimer.restart();
        }
        character.Accelerate(dirToPlayer*0.05f, eTime);
    }

    if(_moveTimer.getElapsedTime().asMilliseconds() >= _moveTime) {
        _moveTimer.restart();

        sf::Vector2f target = character.getPosition();
        float l(MathHelper::GetVecLength(getPosition()-target));
        sf::Vector2f dir((target-getPosition())/l);
        bool canPass = true;
        for(float i=0 ; i<l ; i+=8) {
            sf::FloatRect rect(i*dir + sf::Vector2f(GetGlobalHitbox().left, GetGlobalHitbox().top), sf::Vector2f(GetGlobalHitbox().width, GetGlobalHitbox().height));
            if(level.GetMap().IsCollided(rect, Map::WALL) || level.GetSpawner().IsCollided(rect)) {
                canPass = false;
                break;
            }
        }
        if(!canPass) {
            float angToChar(MathHelper::Rad2Deg(MathHelper::Vec2Ang(character.getPosition()-getPosition())));
            for(int a=0 ; a<10 ; a++) {
                float delta = a/2*36;
                float angle = angToChar+(a%2*2-1)*delta;
                dir = MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle));
                canPass = true;
                for(float i=0 ; i<64 ; i+=8) {
                    sf::FloatRect rect(i*dir + sf::Vector2f(GetGlobalHitbox().left, GetGlobalHitbox().top), sf::Vector2f(GetGlobalHitbox().width, GetGlobalHitbox().height));
                    if(level.GetMap().IsCollided(rect, Map::WALL) || level.GetSpawner().IsCollided(rect)) {
                        canPass = false;
                        break;
                    }
                }
                if(canPass) {
                    break;
                }
            }
        }

        if(canPass) {
            Accelerate(sf::Vector2f(dir)*.04f + sf::Vector2f(0, -.015), eTime);
        }
    }

    Accelerate(sf::Vector2f(0, -.001f), eTime);

    Ennemy::Update(ip, eTime, level, character, eManager, pManager, bManager);

    //update tentacles
    static const float maxL = 2.f;
    for(int i=0 ; i<_tentacles.size() ; i++) {
        for(int j=0 ; j<_tentacles[i].size() ; j++) {
            TentaclePoint& p(_tentacles[i][j]);
            if(j==0) {
                float intX = float(i)/float(_tentacles.size()-1);
                float offY = sin(intX*PI)*5;
                p.pos = sf::Vector2f(getGlobalBounds().left+getGlobalBounds().width*intX, getGlobalBounds().top+getGlobalBounds().height) + sf::Vector2f(0, -offY-1);
            } else {
                TentaclePoint& pp(_tentacles[i][j-1]);
                //p.vel = sf::Vector2f(0, .04*float(j)/float(_tentacles[i].size())*_tentaclesMovement[i]);
                p.pos += p.vel*eTime;
                float curL(MathHelper::GetVecLength(p.pos-pp.pos));
                if(curL > maxL) {
                    sf::Vector2f fDir(MathHelper::Normalize(pp.pos-p.pos));
                    p.pos = pp.pos - fDir*maxL;
                    p.vel += fDir*eTime*.001f;
                }
                p.vel -= p.vel*eTime*.005f;

                //update vertexes
                int id((i*(_tentacles[0].size()-1)+(j-1))*2);
                _tentaclesLines[id].position = pp.pos;
                _tentaclesLines[id+1].position= p.pos;
            }
        }
    }
}

void Jellyfish::Draw(IP& ip) {
    ip._renderer->Draw(_tentaclesLines);
    Ennemy::Draw(ip);
}

void Jellyfish::Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level) {
    Ennemy::Die(ip, pManager, eManager, level);

    /*for(int i=0 ; i<8 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 6, 5) : sf::IntRect(1, 1, 8, 8));
        Particle *p = new Particle(ip, (type == 0 ? "snowRockParticle" : "snowRockParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.2, .5),
                                   MathHelper::RandFloat(-.2, .2),
                                   MathHelper::RandFloat(800, 1200),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }
    for(int i=0 ; i<4 ; i++) {
        int type = rand()%2;
        sf::IntRect hb = (type == 0 ? sf::IntRect(1, 1, 7, 8) : sf::IntRect(1, 1, 7, 10));
        Particle *p = new Particle(ip, (type == 0 ? "fingerParticle" : "fingerParticle2"),
                                   sf::Vector2f(GetGlobalHitbox().left+MathHelper::RandFloat(0, GetGlobalHitbox().width), GetGlobalHitbox().top+MathHelper::RandFloat(0, GetGlobalHitbox().height)),
                                   MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-160, -20))) * MathHelper::RandFloat(.4, .6),
                                   MathHelper::RandFloat(-.3, .3),
                                   MathHelper::RandFloat(1000, 1500),
                                   sf::Vector2f(1, 1),
                                   sf::Vector2f(1, 1),
                                   255,
                                   0,
                                   true,
                                   true,
                                   true,
                                   hb, false);
        pManager.AddParticle(p);
    }*/
}
