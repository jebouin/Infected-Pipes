#ifndef SKILLICON_H_INCLUDED
#define SKILLICON_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Skill;

class SkillIcon : public sf::Sprite {
    public:
    SkillIcon(IP& ip, sf::Vector2i skillPos, string name, string description, Skill& skill);
    ~SkillIcon();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);
    void Unhide();
    bool IsClicked();
    bool IsDoubleClicked();

    private:
    sf::Clock _timer;
    sf::Clock _textBoxTimer;
    sf::Clock _doubleClickTimer;
    sf::Sprite _content;
    sf::Vector2i _skillPos;
    string _name;
    string _description;
    bool _hover;
    bool _hidden;
    bool _clicked;
    bool _canClick;
    bool _doubleClicked;
    bool _canDoubleClick;
    sf::ConvexShape _textBox;
    sf::ConvexShape _doubleClickBox;
    sf::Text _nameText;
    sf::Text _descriptionText;
    sf::Text _levelText;
    sf::Text _doubleClickText;
    Skill &_skill;
};

#endif // SKILLICON_H_INCLUDED
