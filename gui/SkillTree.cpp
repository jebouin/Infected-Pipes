#include "SkillTree.h"
#include "IP.h"
#include "Skill.h"
#include "Renderer.h"
#include "SkillIcon.h"

SkillTree::SkillTree(IP& ip) {
    _ssize = sf::Vector2f(ip._renderer->GetSize());
    string test[3] = {"+10% hp per level", "+10% damage per level", "+5% moving speed\nper level"};
    string titles[3] = {"Health", "Strength", "Agility"};
    for(int j=0 ; j<3 ; j++) {
        for(int i=0 ; i<3 ; i++) {
            Skill *skill = new Skill(ip,
                                sf::Vector2i(32 + i*16, j*16),
                                sf::Vector2f(_ssize/2.f) + sf::Vector2f(float(i-1)*_ssize.x/4.f, _ssize.y/4.f - j*32),
                                titles[i],
                                test[i]);
            if(j==0) {
                skill->Unhide();
            }
            _skills.push_back(skill);
        }
    }
}

SkillTree::~SkillTree() {
    for(int i=0 ; i<_skills.size() ; i++) {
        delete _skills[i];
        _skills[i] = 0;
    }
    _skills.clear();
}

void SkillTree::Update(IP& ip, float eTime) {
    for(int i=0 ; i<_skills.size() ; i++) {
        Skill *skill(_skills[i]);
        skill->Update(ip, eTime);
        if(skill->GetIcon().IsClicked()) {
            if(i/3 < 2) {
                _skills[i+3]->Unhide();
            }
        }
    }
}

void SkillTree::Draw(IP& ip) {
    for(int i=_skills.size()-1 ; i>=0; i--) {
        _skills[i]->Draw(ip);
    }
}
