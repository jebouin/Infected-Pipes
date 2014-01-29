#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "MovingSprite.h"



class IP;
class TextureLoader;
class Level;
class Character;
class ParticleManager;
class GameEntity;
class EntityManager;

class Bullet : public MovingSprite {
    public:
    Bullet(IP& ip, std::string name, sf::IntRect hitbox, sf::Vector2f position, sf::Vector2f vel, int damage, float knockBack, bool animated, bool ennemy, bool gravity, bool instantDie, bool sticky, bool dieOnWall, bool bounce, float penetrationChance);
    virtual ~Bullet();
    virtual void Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager);
    void Draw(IP& ip);
    void TestCollisions(IP& ip, float eTime, Level& level, ParticleManager& pManager, EntityManager& eManager, sf::Vector2f delta);
    void Impact(GameEntity& entity, IP& ip, ParticleManager& pManager, sf::Color color, EntityManager& eManager, Level& level);
    bool IsAlive() const;
    bool IsDying() const;
    bool CollisionWithEnnemies() const;
    void SetCollisionWithEnnemies(bool c);
    virtual bool Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);
    void SetPenetration(float p);

    private:
    bool _gravity;
    bool _alive;
    bool _dying;
    bool _ennemy;
    bool _sticky;
    bool _instantDie;
    bool _inWater;
    bool _collisionWithEnnemies;
    bool _dieOnWall;
    bool _bounce;
    int _damage;
    float _knockBack;
    sf::Clock _deadTimer;
    sf::Clock _timer;
    sf::Vector2f _prevPos;
    float _penetrationChance;

    sf::VertexArray _trail;
};

#endif // BULLET_H_INCLUDED
