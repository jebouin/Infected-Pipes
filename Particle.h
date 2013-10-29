#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "MovingSprite.h"

using namespace std;

class IP;
class Level;
class ParticleManager;

class Particle : public MovingSprite {
    public:
    Particle(IP& ip, string name, sf::Vector2f pos, sf::Vector2f velocity, float rotVel, float lifeTime, sf::Vector2f startScale, sf::Vector2f endScale, float startAlpha, float endAlpha, bool gravity, bool collision, bool animated, sf::IntRect hitbox, bool zFront);
    ~Particle();
    virtual void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager);
    virtual void Draw(IP& ip);
    bool IsAlive();
    bool IsFront();

    private:
    bool _alive;
    float _lifeTime;
    sf::Vector2f _startScale;
    sf::Vector2f _endScale;
    float _startAlpha;
    float _endAlpha;
    sf::Clock _timer;
    bool _gravity;
    bool _collision;
    bool _front;
};

#endif // PARTICLE_H_INCLUDED
