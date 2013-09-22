#include "IP.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Level.h"
#include "EntityManager.h"
#include "Player.h"
#include "Background.h"
#include "Grass.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "GUI.h"
#include "BulletManager.h"

IP::IP() {
    //_window = new sf::RenderWindow(sf::VideoMode(960, 704, 32), "Infected Pipes");
    _window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Infected Pipes", sf::Style::None);
    _window->setVerticalSyncEnabled(true);
    _window->setFramerateLimit(60);
    _window->setMouseCursorVisible(false);
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f));

    _font.loadFromFile("font/font.ttf");
    for(int i=0 ; i<10 ; i++) {
        const sf::Glyph& g(_font.getGlyph('0'+i, 10, false));
    }
    const_cast<sf::Texture&>(_font.getTexture(8)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(16)).setSmooth(false);

    _textureLoader = new TextureLoader(*this);
    _entityManager = new EntityManager();
    _bulletManager = new BulletManager();
    _player = new Player(*this, *_entityManager);
    _level = new Level(*this, _player->GetCharacter());
    _particleManager = new ParticleManager();
    _gui = new GUI(*this, *_textureLoader, _player->GetCharacter(), *_level);

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window->close();
            }
            /*if(e.type == sf::Event::Resized) {
                _renderer = new Renderer(sf::Vector2i(sf::Vector2f(e.size.width, e.size.height)/4.f), 4);
                _player->SetView(sf::View(sf::FloatRect(0, 0, _renderer->GetTexture().getSize().x, _renderer->GetTexture().getSize().y)));
            }*/
        }

        Update();
        Draw();
    }
}

IP::~IP() {
    delete _window;
    delete _renderer;
    delete _textureLoader;
    delete _level;
    delete _entityManager;
    delete _player;
    delete _particleManager;
    delete _gui;
    delete _bulletManager;
}

void IP::Update() {
    float eTime = _clock.restart().asMilliseconds();
    _level->Update(*this, *_entityManager, _player->GetCharacter());
    _entityManager->Update(*this, eTime, *_level, _player->GetCharacter(), *_particleManager, *_bulletManager);
    _player->Update(*this, eTime, *_level, *_entityManager, *_particleManager, *_bulletManager);
    _particleManager->Update(*this, eTime, *_level);
    _bulletManager->Update(*this, eTime, *_level);
    _gui->Update(*this);
}

void IP::Draw() {
    _window->clear();
    _renderer->Clear();

    _level->DrawBack(*this, _player->GetView());
    _entityManager->Draw(*this);
    _player->Draw(*this);
    _particleManager->Draw(*this);
    _bulletManager->Draw(*this);
    _level->DrawFront(*this);

    _renderer->GetTexture().setView(_renderer->GetTexture().getDefaultView());
    _gui->Draw(*this);
    _renderer->GetTexture().setView(_player->GetView());

    _renderer->DrawToWindow(*_window);
    _window->display();
}
