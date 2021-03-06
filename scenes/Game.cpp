#include "Game.h"
#include "IP.h"
#include "Level.h"
#include "EntityManager.h"
#include "Player.h"
#include "Background.h"
#include "ParticleManager.h"
#include "GUI.h"
#include "BulletManager.h"
#include "Renderer.h"
#include "SpeechManager.h"
#include "SpeechBubble.h"
#include "PauseMenu.h"
#include "SceneManager.h"
#include "Cursor.h"
#include "SkillsMenu.h"

Game::Game(IP& ip) : Scene(ip, false) {
    _prevEscapePressed = true;
    _entityManager = new EntityManager();
    _bulletManager = new BulletManager();
    _particleManager = new ParticleManager();
    _speechManager = new SpeechManager();
    _player = new Player(ip, *_entityManager);
    _level = new Level(ip, *_player, *_particleManager);
    _gui = new GUI(ip, _player->GetCharacter(), *_level);
    _speechManager->AddBubble(new SpeechBubble(ip, "Particles! :D", (const GameEntity&)_player->GetCharacter(), 1000, 200));

    ip._cursor->Hide();
}

Game::~Game() {
    delete _level;
    _level = 0;
    delete _entityManager;
    _entityManager = 0;
    delete _gui;
    _gui = 0;
    delete _bulletManager;
    _bulletManager = 0;
    delete _speechManager;
    _speechManager = 0;
    delete _particleManager;
    _particleManager = 0;
    delete _player;
    _player = 0;
}

void Game::Update(float eTime, IP& ip) {
    Scene::Update(eTime, ip);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if(!_prevEscapePressed) {
            ip._sceneManager->AddSceneToAddStack(new PauseMenu(ip));
            ip._cursor->Show();
        }
        _prevEscapePressed = true;
    } else {
        _prevEscapePressed = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        if(!_prevTabPressed) {
            ip._sceneManager->AddSceneToAddStack(new SkillsMenu(ip, _player->GetSkillTree(), *_player));
            ip._cursor->Show();
        }
        _prevTabPressed = true;
        _prevEscapePressed = true;
    } else {
        _prevTabPressed = false;
    }


    ip._renderer->GetTexture().setView(_player->GetView());
    _level->Update(ip, *_entityManager, *_player, eTime, *_particleManager, *_bulletManager, *_gui, _player->GetView());
    _entityManager->Update(ip, eTime, *_level, _player->GetCharacter(), *_particleManager, *_bulletManager);
    _player->Update(ip, eTime, *_level, *_entityManager, *_particleManager, *_bulletManager);
    _bulletManager->Update(ip, eTime, *_level, _player->GetCharacter(), *_particleManager, *_entityManager);
    _particleManager->Update(ip, eTime, *_level);
    _gui->Update(ip, eTime);
    _speechManager->Update(ip, eTime);
}

void Game::Draw(IP& ip) {
    Scene::Draw(ip);

    _level->DrawBack(ip, _player->GetView());
    _entityManager->Draw(ip);
    _player->Draw(ip);
    _particleManager->DrawBack(ip);
    _bulletManager->Draw(ip);
    _level->DrawFront(ip, _player->GetView());
    _player->DrawFront(ip);
    _speechManager->Draw(ip);
    _particleManager->DrawFront(ip);

    ip._renderer->GetTexture().setView(ip._renderer->GetTexture().getDefaultView());
    _gui->Draw(ip);

    //always leave this method with the basic view
}
