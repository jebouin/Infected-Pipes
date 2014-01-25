#include "SkillsMenu.h"
#include "IP.h"
#include "SceneManager.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "Cursor.h"
#include "MainMenu.h"
#include "SkillIcon.h"

SkillsMenu::SkillsMenu(IP& ip)
    : Scene(ip, true) {
    _ssize = sf::Vector2f(ip._renderer->GetSize());
    _view = sf::View(sf::FloatRect(sf::Vector2f(0, 0), _ssize));
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

    string test[3] = {"each level +10% hp", "each level +10% hp\nTest", "HA\nHA\nHA\nHA"};
    for(int i=0 ; i<3 ; i++) {
        SkillIcon* icon = new SkillIcon(ip, sf::Vector2i(17, 0), "Health", test[i]);
        icon->setPosition(sf::Vector2f(_ssize/2.f) + sf::Vector2f(float(i-1)*_ssize.x/4.f, _ssize.y/4.f));
        _icons.push_back(icon);
    }
}

SkillsMenu::~SkillsMenu() {
    for(int i=0 ; i<_icons.size() ; i++) {
        delete _icons[i];
        _icons[i] = 0;
    }
    _icons.clear();
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
    for(int i=0 ; i<_icons.size() ; i++) {
        _icons[i]->Update(ip, eTime);
    }
}

void SkillsMenu::Draw(IP& ip) {
    Scene::Draw(ip);
    ip._renderer->GetTexture().setView(ip._renderer->GetTexture().getDefaultView());
    ip._renderer->Draw(_back);

    ip._renderer->Draw(_title);
    for(int i=0 ; i<_icons.size() ; i++) {
        _icons[i]->Draw(ip);
    }
}
