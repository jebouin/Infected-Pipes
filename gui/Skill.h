#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class SkillIcon;

class Skill {
    public:
    Skill(IP& ip, sf::Vector2i skillPos, sf::Vector2f iconPos, string name, string description, int maxLevel);
    ~Skill();
    void Update(IP& ip, float eTime);
    void DrawBack(IP& ip);
    void DrawTop(IP& ip);
    int GetLevel();
    int GetLevelMax();
    void LevelUp();
    SkillIcon& GetIcon();
    void Unhide();

    private:
    SkillIcon *_icon;
    int _level;
    int _maxLevel;
};

#endif // SKILL_H_INCLUDED
