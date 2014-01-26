#ifndef SKILLTREE_H_INCLUDED
#define SKILLTREE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Skill;

class SkillTree {
    public:
    SkillTree(IP& ip);
    ~SkillTree();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);

    private:
    vector<Skill*> _skills;
    sf::Vector2f _ssize;
};

#endif // SKILLICON_H_INCLUDED
