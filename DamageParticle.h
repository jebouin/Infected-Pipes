#ifndef DAMAGEPARTICLE_H_INCLUDED
#define DAMAGEPARTICLE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Particle.h"

using namespace std;

class IP;

class DamageParticle : public Particle {
    public:
    DamageParticle(IP& ip, int damage, sf::Vector2f pos, sf::Vector2f velocity, sf::Vector2f startScale, sf::Vector2f endScale, bool gravity, bool collision);
    ~DamageParticle();
    void Update(IP& ip, float eTime, Level& level);
    void Draw(IP& ip);

    private:
    //sf::RenderTexture _texture;
    sf::Text _text;
};

#endif // DAMAGEPARTICLE_H_INCLUDED
