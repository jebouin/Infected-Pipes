#ifndef SPEECHBUBBLE_H_INCLUDED
#define SPEECHBUBBLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class GameEntity;

class SpeechBubble : public sf::ConvexShape {
public:
    SpeechBubble(IP& ip, std::string text, const GameEntity& speaker, float stayTime, float fadeTime);
    ~SpeechBubble();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);
    bool IsAlive();

private:
    sf::Text _text;
    const GameEntity& _speaker;
    sf::FloatRect _upperRect;
    float _stayTime;
    float _fadeTime;
    sf::Clock _timer;
    bool _alive;
    bool _fading;
};

#endif // SPEECHBUBBLE_H_INCLUDED
