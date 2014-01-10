#include "MainMenu.h"
#include "IP.h"
#include "MainMenuBackground.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "Game.h"
#include "SceneManager.h"

MainMenu::MainMenu(IP& ip) : Scene(ip) {
    _title.setTexture(ResourceLoader::GetTexture("title"));
    _title.setOrigin(sf::Vector2f(sf::Vector2i(_title.getTextureRect().width, _title.getTextureRect().height)/2));
    _title.setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2.f, ip._renderer->GetTexture().getSize().y/5.f));

    _background = new MainMenuBackground(ip);
}

MainMenu::~MainMenu() {
    delete _background;
    _background = 0;
}

void MainMenu::Update(float eTime, IP& ip) {
    Scene::Update(eTime, ip);
    _background->Update(ip, eTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        ip._sceneManager->RemoveScene();
        ip._sceneManager->AddScene(new Game(ip));
    }
}

void MainMenu::Draw(IP& ip) {
    Scene::Draw(ip);

    _background->Draw(ip);
    ip._renderer->GetTexture().setView(ip._renderer->GetTexture().getDefaultView());
    ip._renderer->Draw(_title);
}
