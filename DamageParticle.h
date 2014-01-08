#ifndef DAMAGEPARTICLE_H_INCLUDED
#define DAMAGEPARTICLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Particle.h"



class IP;

class DamageParticle : public Particle {
    public:
    DamageParticle(IP& ip, int damage, sf::Vector2f pos, sf::Vector2f velocity, sf::Vector2f startScale, sf::Vector2f endScale, sf::Color color, bool gravity, bool collision);
    ~DamageParticle();
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);

    private:
    //sf::RenderTexture _texture;
    sf::Text _text;
};

#endif // DAMAGEPARTICLE_H_INCLUDED
