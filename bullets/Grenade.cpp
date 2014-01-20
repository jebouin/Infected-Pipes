#include "Grenade.h"
#include "IP.h"
#include "Character.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "Particle.h"
#include "Renderer.h"

Grenade::Grenade(IP& ip, sf::Vector2f position, sf::Vector2f vel, bool ennemy) : Bullet(ip, "grenade", sf::IntRect(0, 2, 6, 5), position, vel, 0, .1, true, ennemy, true, true, false, false, true) {
    SetCollisionWithEnnemies(false);
    SetBounce(true);
}

Grenade::~Grenade() {

}

void Grenade::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    Bullet::Update(ip, eTime, level, character, pManager, eManager);

    if(_explosionTimer.getElapsedTime().asMilliseconds() >= 2000) {
        Die(ip, pManager, eManager, level);
        ip._renderer->AddFlash(80, .8);
        Particle *p = new Particle(ip,
                                   "bigExplosion",
                                   getPosition(),
                                   sf::Vector2f(0, 0), 0.,
                                   240,
                                   sf::Vector2f(1., 1.),
                                   sf::Vector2f(1., 1.),
                                   255,
                                   255,
                                   false,
                                   false,
                                   true,
                                   sf::IntRect(42, 42, 42, 42),
                                   true);
        p->GetAnims().AddAnimation("base", new Animation(8, 20, sf::Vector2i(0, 0), sf::Vector2i(25, 25), false));
        p->GetAnims().SetAnimation("base");
        pManager.AddParticle(p);
    }
}

void Grenade::Draw(IP& ip) {
    Bullet::Draw(ip);
}
