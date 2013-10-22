#ifndef MOVINGSPRITE_H_INCLUDED
#define MOVINGSPRITE_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;
class AnimationTable;
class ParticleManager;

class MovingSprite : public sf::Sprite {
    public:
    MovingSprite(IP& ip, string name, bool animated=true);
    MovingSprite(IP& ip, string name, sf::IntRect hitbox, bool animated=true);
    ~MovingSprite();
    void Update(IP& ip, float eTime);
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    void MoveCollidingMap(sf::Vector2f delta, Level& level);
    bool TryMove(sf::Vector2f delta, Level& level);
    sf::Vector2f GetVel();
    float GetRotVel();
    sf::Vector2f GetLocalUpperLeftPos() const;
    sf::Vector2f GetGlobalUpperLeftPos() const;
    sf::IntRect GetHitbox();
    sf::FloatRect GetGlobalHitbox();
    AnimationTable& GetAnims();
    bool OnPlatform();
    bool IsInWater(Level& level);
    void SetVel(sf::Vector2f vel);
    void Accelerate(sf::Vector2f vec, float eTime);
    void SetRotVel(float rotVel);
    void SetUpperLeftCorner(sf::Vector2f pos);
    void SetHitbox(sf::IntRect rect);
    void SetOnPlatform(bool on);
    void SetCollideOnPlatform(bool c);
    void SetCollideWithWater(bool c);
    void SetCollisionPrecision(float p);

    protected:
    void WaterCollision(Level& l, sf::Vector2f deltaPos, ParticleManager& pManager, IP& ip);
    sf::Vector2f _prevPos;

    private:
    AnimationTable *_animTable;

    sf::IntRect _hitbox;
    sf::Vector2f _vel;
    float _rotVel;
    float _collisionPrecision;
    bool _onPlatform;
    bool _collidesWithPlatform;
    bool _collidesWithWater;
    bool _animated;

    sf::ConvexShape _box;
};

#endif // MOVINGSPRITE_H_INCLUDED
