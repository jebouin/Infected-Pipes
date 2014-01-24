#ifndef SKILLICON_H_INCLUDED
#define SKILLICON_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;

class SkillIcon : public sf::Sprite {
    public:
    SkillIcon(IP& ip, sf::Vector2i skillPos, string name);
    ~SkillIcon();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);

    private:
    sf::Clock _timer;
    sf::Clock _textBoxTimer;
    sf::Sprite _content;
    string _name;
    bool _hover;
    sf::ConvexShape _textBox;
    sf::Text _nameText;
};

#endif // SKILLICON_H_INCLUDED
