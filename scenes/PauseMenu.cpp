#include "PauseMenu.h"
#include "IP.h"
#include "SceneManager.h"
#include "MathHelper.h"
#include "Renderer.h"

PauseMenu::PauseMenu(IP& ip)
    : Scene(ip, true) {
    sf::Vector2f ssize(ip._renderer->GetSize());
    _view = sf::View(sf::FloatRect(sf::Vector2f(0, 0), ssize));
    _back.setFillColor(sf::Color(0, 0, 0, 160));
    _back.setPointCount(4);
    vector<sf::Vector2f> c(MathHelper::Rect2Corners(sf::FloatRect(sf::Vector2f(0, 0), ssize)));
    for(int i=0 ; i<4 ; i++) {
        _back.setPoint(i, c[i]);
    }
    _prevEscapePressed = true;
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::Update(float eTime, IP& ip) {
    Scene::Update(eTime, ip);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if(!_prevEscapePressed) {
            ip._sceneManager->RemoveScene();
        }
        _prevEscapePressed = true;
    } else {
        _prevEscapePressed = false;
    }
}

void PauseMenu::Draw(IP& ip) {
    Scene::Draw(ip);
    ip._renderer->GetTexture().setView(_view);
    ip._renderer->Draw(_back);
}
