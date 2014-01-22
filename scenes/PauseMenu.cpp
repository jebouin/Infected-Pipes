#include "PauseMenu.h"
#include "IP.h"
#include "SceneManager.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "Cursor.h"
#include "MainMenu.h"

PauseMenu::PauseMenu(IP& ip)
    : Scene(ip, true), _baseColor(104, 99, 85), _selecColor(211, 211, 211) {
    _ssize = sf::Vector2f(ip._renderer->GetSize());
    _view = sf::View(sf::FloatRect(sf::Vector2f(0, 0), _ssize));
    _back.setFillColor(sf::Color(0, 0, 0, 200));
    _back.setPointCount(4);
    vector<sf::Vector2f> c(MathHelper::Rect2Corners(sf::FloatRect(sf::Vector2f(0, 0), _ssize)));
    for(int i=0 ; i<4 ; i++) {
        _back.setPoint(i, c[i]);
    }
    _prevEscapePressed = true;

    _pause.setFont(ip._font);
    _pause.setCharacterSize(32);
    _pause.setString("PAUSE");
    _pause.setColor(sf::Color(175, 167, 72));

    _resume.setFont(ip._font);
    _resume.setCharacterSize(24);
    _resume.setString("RESUME");
    _resume.setPosition(sf::Vector2f(_ssize.x / 2.f - _resume.getGlobalBounds().width/2.f, _ssize.y / 3.f - _resume.getGlobalBounds().height/2.f + 10));

    _options.setFont(ip._font);
    _options.setCharacterSize(24);
    _options.setString("OPTIONS");
    _options.setPosition(sf::Vector2f(_ssize.x / 2.f - _options.getGlobalBounds().width/2.f, _ssize.y / 2.f - _options.getGlobalBounds().height/2.f + 10));

    _quit.setFont(ip._font);
    _quit.setCharacterSize(24);
    _quit.setString("QUIT");
    _quit.setPosition(sf::Vector2f(_ssize.x / 2.f - _quit.getGlobalBounds().width/2.f, _ssize.y / 3.f * 2.f - _quit.getGlobalBounds().height/2.f + 10));
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::Update(float eTime, IP& ip) {
    Scene::Update(eTime, ip);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if(!_prevEscapePressed) {
            ip._sceneManager->RemoveScene();
            ip._cursor->Hide();
        }
        _prevEscapePressed = true;
    } else {
        _prevEscapePressed = false;
    }

    float time = _timer.getElapsedTime().asMilliseconds();
    float pauseyd = sin(time/1000.f*2*PI)*3;
    _pause.setPosition(sf::Vector2f(_ssize.x / 2.f - _pause.getGlobalBounds().width/2.f, _ssize.y / 8.f - _pause.getGlobalBounds().height/2.f - 10 + pauseyd));

    sf::Vector2f mpos = sf::Vector2f(sf::Mouse::getPosition(*ip._window)) / 4.f;
    bool onResume=false, onOptions=false, onQuit=false;
    if(_resume.getGlobalBounds().contains(mpos)) {
        onResume = true;
    }
    if(_options.getGlobalBounds().contains(mpos)) {
        onOptions = true;
    }
    if(_quit.getGlobalBounds().contains(mpos)) {
        onQuit = true;
    }

    if(onResume) {
        _resume.setColor(_selecColor);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            ip._sceneManager->RemoveScene();
            ip._cursor->Hide();
        }
    } else {
        _resume.setColor(_baseColor);
    }
    if(onOptions) {
        _options.setColor(_selecColor);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        }
    } else {
        _options.setColor(_baseColor);
    }
    if(onQuit) {
        _quit.setColor(_selecColor);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            ip._sceneManager->RemoveScene();
            ip._sceneManager->RemoveScene();
            ip._sceneManager->AddScene(new MainMenu(ip));
        }
    } else {
        _quit.setColor(_baseColor);
    }
}

void PauseMenu::Draw(IP& ip) {
    Scene::Draw(ip);
    ip._renderer->GetTexture().setView(_view);
    ip._renderer->Draw(_back);

    ip._renderer->Draw(_pause);
    ip._renderer->Draw(_resume);
    ip._renderer->Draw(_options);
    ip._renderer->Draw(_quit);
}
