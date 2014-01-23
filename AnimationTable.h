#ifndef ANIMATIONTABLE_H_INCLUDED
#define ANIMATIONTABLE_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class Animation;

class AnimationTable {
    public:
    AnimationTable();
    ~AnimationTable();
    void Update();
    void SetAnimation(std::string name);
    void AddAnimation(std::string name, Animation anim);
    Animation& GetAnimation(std::string name);
    Animation& GetAnimation();
    std::string GetAnimationName();
    sf::IntRect GetRect();

    private:
    std::string _curAnim;
    std::map<std::string, Animation> _animations;
};

#endif // ANIMATIONTABLE_H_INCLUDED
