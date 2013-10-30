#ifndef WAVEINDICATOR_H_INCLUDED
#define WAVEINDICATOR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class TextureLoader;
class Level;
class MovingSprite;

class WaveIndicator {
    public:
    WaveIndicator(IP& ip);
    ~WaveIndicator();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);
    void AnnounceWave(IP& ip, int nb);

    private:
    sf::Clock _timer;
    sf::Text _text;
    sf::Sprite *_top;
    sf::Sprite *_bottom;
    sf::RenderTexture _rt;
    float _speed;
    bool _announcing;
    bool _passed;
};

#endif // WAVEINDICATORINCLUDED
