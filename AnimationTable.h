#ifndef ANIMATIONTABLE_H_INCLUDED
#define ANIMATIONTABLE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class Animation;

class AnimationTable {
    public:
    AnimationTable();
    ~AnimationTable();
    void Update();
    void SetAnimation(string name);
    void AddAnimation(string name, Animation *anim);
    Animation& GetAnimation(string name);
    Animation& GetAnimation();
    string GetAnimationName();
    sf::IntRect GetRect();

    private:
    string _curAnim;
    map<string, Animation*> _animations;
};

#endif // ANIMATIONTABLE_H_INCLUDED
