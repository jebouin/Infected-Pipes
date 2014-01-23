#include "FireBallBullet.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "Particle.h"

FireBallBullet::FireBallBullet(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "fireBallBullet", sf::IntRect(0, 0, 6, 8), position, vel, 30, .6, true, ennemy, false, true, false, true, false) {
    AnimationTable& t(GetAnims());
    t.AddAnimation("anim", Animation(4, 100, sf::Vector2i(0, 0), sf::Vector2i(6, 8), true));
    t.SetAnimation("anim");
}

FireBallBullet::~FireBallBullet() {

}

void FireBallBullet::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    if(!IsDying()) {
        setRotation(MathHelper::Rad2Deg(MathHelper::Vec2Ang(GetVel())));
    }
    Bullet::Update(ip, eTime, level, character, pManager, eManager);

    if(rand()%3==0) {
        pManager.AddParticle(new Particle(ip, "fireParticle",
                                          getPosition(),
                                          sf::Vector2f(0., MathHelper::RandFloat(-.03, .03)),
                                          0.,
                                          MathHelper::RandFloat(300, 600),
                                          sf::Vector2f(1, 1),
                                          sf::Vector2f(1, 1),
                                          255,
                                          0,
                                          false,
                                          false,
                                          false,
                                          sf::IntRect(1, 1, 3, 3), false));
    }
    if(!IsAlive()) {
        for(int i=0 ; i<8 ; i++) {
            pManager.AddParticle(new Particle(ip, "fireParticle",
                                              getPosition(),
                                              MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360))) * MathHelper::RandFloat(.1, .3),
                                              0.,
                                              MathHelper::RandFloat(300, 600),
                                              sf::Vector2f(1, 1),
                                              sf::Vector2f(1, 1),
                                              255,
                                              0,
                                              false,
                                              false,
                                              false,
                                              sf::IntRect(1, 1, 3, 3), false));
        }
    }
}

void FireBallBullet::Draw(IP& ip) {
    Bullet::Draw(ip);
}
