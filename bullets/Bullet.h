#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "MovingSprite.h"

using namespace std;

class IP;
class TextureLoader;
class Level;
class Character;
class ParticleManager;
class GameEntity;
class EntityManager;

class Bullet : public MovingSprite {
    public:
    Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, int damage, float knockBack, bool animated, bool ennemy, bool gravity, bool instantDie, bool sticky);
    ~Bullet();
    virtual void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);
    void TestCollisions(IP& ip, float eTime, Level& level, sf::Vector2f delta);
    void Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color, EntityManager& eManager, Level& level);
    bool IsAlive() const;
    bool IsDying() const;

    private:
    bool _gravity;
    bool _alive;
    bool _dying;
    bool _ennemy;
    bool _sticky;
    bool _instantDie;
    bool _inWater;
    int _damage;
    float _knockBack;
    sf::Clock _deadTimer;
    sf::Clock _timer;
};

#endif // BULLET_H_INCLUDED
