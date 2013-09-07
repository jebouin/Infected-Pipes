#ifndef MOVINGSPRITE_H_INCLUDED
#define MOVINGSPRITE_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;
class AnimationTable;

class MovingSprite : public sf::Sprite {
    public:
    MovingSprite(IP& ip, string name);
    MovingSprite(IP& ip, string name, sf::IntRect hitbox);
    ~MovingSprite();
    void Update(IP& ip, float eTime);
    void Update(IP& ip, float eTime, Level& level);
    bool TryMove(sf::Vector2f delta, Level& level);
    sf::Vector2f GetVel();
    float GetRotVel();
    sf::Vector2f GetUpperLeftPos();
    sf::IntRect GetHitbox();
    sf::FloatRect GetGlobalHitbox();
    AnimationTable& GetAnims();
    void SetVel(sf::Vector2f vel);
    void Accelerate(sf::Vector2f vec, float eTime);
    void SetRotVel(float rotVel);
    void SetHitbox(sf::IntRect rect);

    private:
    AnimationTable *_animTable;

    sf::IntRect _hitbox;
    sf::Vector2f _vel;
    float _rotVel;
};

#endif // MOVINGSPRITE_H_INCLUDED
