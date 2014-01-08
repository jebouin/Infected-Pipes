#ifndef CHEST_H_INCLUDED
#define CHEST_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "MovingSprite.h"



class IP;
class Level;
class ChestOpened;

class Chest : public MovingSprite {
    public:
    Chest(IP& ip, sf::Vector2f pos);
    ~Chest();
    void Update(IP& ip, float eTime, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    void Open(IP& ip);

    private:
    ChestOpened *_chestOpened;
    bool _opened;
};

#endif // CHEST_H_INCLUDED
