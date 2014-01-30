#ifndef HEALINGPARTICLE_H_INCLUDED
#define HEALINGPARTICLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Particle.h"

class IP;

class HealingParticle : public Particle {
    public:
    HealingParticle(IP& ip, int amount, sf::Vector2f pos);
    ~HealingParticle();
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);

    private:
    sf::Text _text;
};

#endif // HEALINGPARTICLE_H_INCLUDED
