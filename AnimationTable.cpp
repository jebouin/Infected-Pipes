#include "AnimationTable.h"
#include "Animation.h"

AnimationTable::AnimationTable() {

}

AnimationTable::~AnimationTable() {
    for(map<string, Animation*>::iterator i=_animations.begin() ; i!=_animations.end() ; i++) {
        delete i->second;
    }
}

void AnimationTable::Update() {
    _animations[_curAnim]->Update();
}

void AnimationTable::SetAnimation(string name) {
    _curAnim = name;
    _animations[_curAnim]->Restart();
}

void AnimationTable::AddAnimation(string name, Animation *anim) {
    _animations[name] = anim;
}

Animation& AnimationTable::GetAnimation(string name) {
    return *_animations[name];
}

Animation& AnimationTable::GetAnimation() {
    return *_animations[_curAnim];
}

string AnimationTable::GetAnimationName() {
    return _curAnim;
}

sf::IntRect AnimationTable::GetRect() {
    return _animations.at(_curAnim)->GetRect();
}
