#ifndef LEVELINDICATOR_H_INCLUDED
#define LEVELINDICATOR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Character;
class TextureLoader;

class LevelIndicator : public sf::Sprite {
    public:
    LevelIndicator(IP& ip, Character& character, TextureLoader& tLoader);
    ~LevelIndicator();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    const Character& _character;
    sf::Text _levelText;
    sf::Text _nbText;
};

#endif // INDICATOR_H_INCLUDED
