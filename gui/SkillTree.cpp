#include "SkillTree.h"
#include "IP.h"
#include "Skill.h"
#include "Renderer.h"
#include "SkillIcon.h"
#include "Player.h"

SkillTree::SkillTree(IP& ip) {
    _ssize = sf::Vector2f(ip._renderer->GetSize());
    string titles[9] = {"Health", "Strength", "Agility", "Healing", "Attack Speed", "Jump height", "Healing fly", "Ground attack", "Dash"};
    string descriptions[9] = {"Increases max health\n+10% hp per level",
                                "Increases attack strength\n+10% damage per level",
                                "Increases running speed\n+5% moving speed\nper level",
                                "Increases healing speed\nLevel 1: +1hp/s\nLevel 2: +8hp/s\nLevel 3: +25hp/s",
                                "Increases attack speed\nLevel 1: +10%\nLevel 2: +25%\nLevel 3: +60%",
                                "Increases jump height\nLevel 1: +15%\nLevel 2: +30%\nLevel 3: +50%",
                                "Summons magical flies\nthat will heal you\nduring your adventure\nLevel 1: 1 fly\nLevel 2: 3 flies\nLevel 3: 8 flies",
                                "Learn a powerful attack\nthat will damage enemies\nwhen falling on the ground",
                                "Learn how to dash\n1 dash per level"};
    for(int j=0 ; j<3 ; j++) {
        for(int i=0 ; i<3 ; i++) {
            Skill *skill = new Skill(ip,
                                sf::Vector2i(32 + i*16, j*16),
                                sf::Vector2f(_ssize/2.f) + sf::Vector2f(float(i-1)*(_ssize.x/4.f-8.f), _ssize.y/4.f - j*32),
                                titles[j*3+i],
                                descriptions[j*3+i],
                                3);
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

void SkillTree::Update(IP& ip, float eTime, Player& player) {
    for(int i=0 ; i<_skills.size() ; i++) {
        Skill *skill(_skills[i]);
        skill->Update(ip, eTime);
        if(skill->GetIcon().IsDoubleClicked()) {
            skill->LevelUp();
            LearnSkill(player, i);
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

void SkillTree::LearnSkill(Player& player, int id) {
    Skill* skill(_skills[id]);
    int level(skill->GetLevel());
    int levelMax(skill->GetLevelMax());
}
