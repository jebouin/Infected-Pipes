#ifndef SPEECHBUBBLE_H_INCLUDED
#define SPEECHBUBBLE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class GameEntity;

class SpeechBubble : public sf::ConvexShape {
public:
    SpeechBubble(IP& ip, string text, const GameEntity& speaker);
    ~SpeechBubble();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);

private:
    sf::Text _text;
    const GameEntity& _speaker;
    sf::FloatRect _upperRect;
};

#endif // SPEECHBUBBLE_H_INCLUDED