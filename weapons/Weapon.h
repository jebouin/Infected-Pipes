#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;
class EntityManager;
class Level;
class ParticleManager;

class Weapon {
    public:
    Weapon(IP& ip, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime);
    virtual ~Weapon();
    virtual void Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager);
    virtual void Draw(IP& ip);
    virtual bool Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager);
    sf::Vector2f GetPosition();
    void SetRelPosition(sf::Vector2f p);
    void SetReloadSpeedMultiplier(float mult);

    protected:
    sf::Vector2f _position;

    private:
    const GameEntity& _holder;
    sf::Clock _useTimer;
    float _baseReloadTime;
    float _reloadTime;
    sf::Vector2f _relativePos;
};

#endif // WEAPON_H_INCLUDED
