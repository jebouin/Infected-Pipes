#include "SkillsMenu.h"
#include "IP.h"
#include "SceneManager.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "Cursor.h"
#include "MainMenu.h"
#include "SkillTree.h"
#include "Player.h"

SkillsMenu::SkillsMenu(IP& ip, SkillTree& skillTree, Player& player)
    : Scene(ip, true), _skillTree(skillTree), _player(player) {
    _ssize = sf::Vector2f(ip._renderer->GetSize());
    _back.setFillColor(sf::Color(0, 0, 0, 200));
    _back.setPointCount(4);
    vector<sf::Vector2f> c(MathHelper::Rect2Corners(sf::FloatRect(sf::Vector2f(0, 0), _ssize)));
    for(int i=0 ; i<4 ; i++) {
        _back.setPoint(i, c[i]);
    }
    _prevEscapePressed = true;

    _title.setFont(ip._font);
    _title.setCharacterSize(24);
    _title.setString("PLAYER SKILLS");
    _title.setColor(sf::Color(175, 167, 72));
    _title.setPosition(sf::Vector2f(_ssize.x / 2.f - _title.getGlobalBounds().width/2.f, 0));
}

SkillsMenu::~SkillsMenu() {

}

void SkillsMenu::Update(float eTime, IP& ip) {
    Scene::Update(eTime, ip);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        if(!_prevEscapePressed) {
            ip._sceneManager->AddSceneToRemoveStack();
            ip._cursor->Hide();
        }
        _prevEscapePressed = true;
    } else {
        _prevEscapePressed = false;
    }
    _skillTree.Update(ip, eTime, _player);
}

void SkillsMenu::Draw(IP& ip) {
    Scene::Draw(ip);
    ip._renderer->GetTexture().setView(ip._renderer->GetTexture().getDefaultView());
    ip._renderer->Draw(_back);

    ip._renderer->Draw(_title);
    _skillTree.Draw(ip);
}
