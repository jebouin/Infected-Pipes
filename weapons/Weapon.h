#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class TextureLoader;
class GameEntity;
class BulletManager;

class Weapon {
    public:
    Weapon(IP& ip, const GameEntity& holder, sf::Vector2f relativePos, float reloadTime);
    virtual ~Weapon();
    virtual void Update(IP& ip, float eTime, BulletManager& bManager);
    virtual void Draw(IP& ip);
    virtual bool Use(IP& ip, BulletManager& bManager, float angle);
    sf::Vector2f GetPosition();
    void SetRelPosition(sf::Vector2f p);

    private:
    const GameEntity& _holder;
    sf::Clock _useTimer;
    float _reloadTime;
    sf::Vector2f _relativePos;
    sf::Vector2f _position;
};

#endif // WEAPON_H_INCLUDED
