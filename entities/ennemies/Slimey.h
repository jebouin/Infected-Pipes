#ifndef SLIMEY_H_INCLUDED
#define SLIMEY_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"



class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

class Slimey : public Ennemy {
    public:
    Slimey(IP& ip, Level& level);
    ~Slimey();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void Damage(int dmg, IP& ip, ParticleManager& pManager, sf::Color color, sf::Vector2f pos, sf::Vector2f dir, EntityManager& eManager, Level& level);

    private:
    sf::Clock _attackTimer;
    sf::Clock _jumpTimer;
    float _nextJump;
    int _prevState;
};

#endif // SLIMEY_H_INCLUDED
