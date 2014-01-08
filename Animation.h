#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <cmath>



#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Animation {
    public:
    Animation(int nbFrames, float frameTime, sf::Vector2i pos, sf::Vector2i size, bool loop);
    ~Animation();
    void Update();
    void Restart();
    int GetCurFrame();
    sf::IntRect GetRect();
    bool IsFinished();

    private:
    sf::Clock _timer;
    int _curFrame;
    int _nbFrames;
    float _frameTime;
    sf::Vector2i _pos;
    sf::Vector2i _size;
    bool _loop;
    bool _finished;
};

#endif // ANIMATION_H_INCLUDED
