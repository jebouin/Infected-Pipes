#ifndef JELLYFISH_H_INCLUDED
#define JELLYFISH_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Jellyfish : public Ennemy {
    public:
    Jellyfish(IP& ip, Level& level);
    ~Jellyfish();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
    sf::Clock _moveTimer;
    float _moveTime;

};

#endif // JELLYFISH_H_INCLUDED
