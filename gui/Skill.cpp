#include "Skill.h"
#include "IP.h"
#include "SkillIcon.h"

Skill::Skill(IP& ip, sf::Vector2i skillPos, sf::Vector2f iconPos, string name, string description) {
    _icon = new SkillIcon(ip, skillPos, name, description);
    _icon->setPosition(iconPos);
}

Skill::~Skill() {
    delete _icon;
    _icon = 0;
}

void Skill::Update(IP& ip, float eTime) {
    _icon->Update(ip, eTime);
}

void Skill::Draw(IP& ip) {
    _icon->Draw(ip);
}

int Skill::GetLevel() {
    return _level;
}

void Skill::LevelUp() {
    if(_level == _maxLevel) {
        return;
    }
    _level++;
}

SkillIcon& Skill::GetIcon() {
    return *_icon;
}

void Skill::Unhide() {
    _icon->Unhide();
}
