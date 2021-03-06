#ifndef SKILLSMENU_H_INCLUDED
#define SKILLSMENU_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Scene.h"

using namespace std;

class IP;
class SkillIcon;
class SkillTree;
class Player;

class SkillsMenu : public Scene {
public:
    SkillsMenu(IP& ip, SkillTree& skillTree, Player& player);
    ~SkillsMenu();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);

private:
    sf::Clock _timer;
    sf::ConvexShape _back;
    bool _prevEscapePressed;
    sf::Vector2f _ssize;
    sf::Text _title;

    SkillTree& _skillTree;
    Player& _player;
};

#endif //SKILLSMENU_H_INCLUDED
