#ifndef HEALINGFLY_H_INCLUDED
#define HEALINGFLY_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class Level;
class ParticleManager;
class Character;
class AnimationTable;

class HealingFly : public sf::Sprite {
public:
    HealingFly(IP& ip);
    ~HealingFly();
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager, Character& character);
    void Draw(IP& ip);

private:
    void NewHealingTime();

    AnimationTable *_anims;
    AnimationTable *_heartAnims;
    sf::Vector2f _vel;
    sf::Clock _moveTimer;
    sf::Clock _healingTimer;
    sf::Sprite _heart;
    bool _healing;
    float _healingProgress;
    float _nextHealingTime;
};

#endif // HEALINGFLY_H_INCLUDED
