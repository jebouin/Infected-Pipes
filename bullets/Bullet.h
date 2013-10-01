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
    Bullet(IP& ip, string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, int damage, bool animated, bool ennemy, bool gravity);
    ~Bullet();
    virtual void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);
    void Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color);
    bool IsAlive() const;

    private:
    bool _gravity;
    bool _alive;
    bool _dying;
    bool _ennemy;
    int _damage;
    sf::Clock _deadTimer;
};

#endif // BULLET_H_INCLUDED
