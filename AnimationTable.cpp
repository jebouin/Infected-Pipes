#include "AnimationTable.h"
#include "Animation.h"

AnimationTable::AnimationTable() {

}

AnimationTable::~AnimationTable() {
    /*for(std::map<std::string, Animation*>::iterator i=_animations.begin() ; i!=_animations.end() ; i++) {
        delete i->second;
        i->second = 0;
    }
    _animations.clear();*/
}

void AnimationTable::Update() {
    _animations[_curAnim].Update();
}

void AnimationTable::SetAnimation(std::string name) {
    _curAnim = name;
    _animations[_curAnim].Restart();
}

void AnimationTable::AddAnimation(std::string name, Animation anim) {
    _animations[name] = Animation(anim);
}

Animation& AnimationTable::GetAnimation(std::string name) {
    return _animations[name];
}

Animation& AnimationTable::GetAnimation() {
    return _animations[_curAnim];
}

std::string AnimationTable::GetAnimationName() {
    return _curAnim;
}

sf::IntRect AnimationTable::GetRect() {
    return _animations.at(_curAnim).GetRect();
}
