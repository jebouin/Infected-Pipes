#ifndef SKILLTREE_H_INCLUDED
#define SKILLTREE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Skill;
class Player;

class SkillTree {
    public:
    SkillTree(IP& ip);
    ~SkillTree();
    void Update(IP& ip, float eTime, Player& player);
    void Draw(IP& ip);
    void LearnSkill(IP& ip, Player& player, int id);

    private:
    vector<Skill*> _skills;
    sf::Vector2f _ssize;
    sf::VertexArray _links;
};

#endif // SKILLICON_H_INCLUDED
