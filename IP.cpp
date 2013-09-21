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

IP::IP() {
    _window = new sf::RenderWindow(sf::VideoMode(960, 704, 32), "Infected Pipes");
    _window->setVerticalSyncEnabled(true);
    _window->setFramerateLimit(60);
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f));

    _font.loadFromFile("font/font.ttf");
    for(int i=0 ; i<10 ; i++) {
        const sf::Glyph& g(_font.getGlyph('0'+i, 10, false));
    }

    _textureLoader = new TextureLoader(*this);
    _entityManager = new EntityManager();
    _player = new Player(*this, *_entityManager);
    _level = new Level(*this, _player->GetCharacter());
    _particleManager = new ParticleManager();
    _gui = new GUI(*this, *_textureLoader, _player->GetCharacter());

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
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
}

void IP::Update() {
    float eTime = _clock.restart().asMilliseconds();
    _level->Update(*this, *_entityManager, _player->GetCharacter());
    _entityManager->Update(*this, eTime, *_level, _player->GetCharacter(), *_particleManager);
    _player->Update(*this, eTime, *_level, *_entityManager, *_particleManager);
    _particleManager->Update(*this, eTime, *_level);
    _gui->Update(*this);
}

void IP::Draw() {
    /*sf::View v(_window->getDefaultView());  //test
    v.zoom(0.5f);
    _window->setView(v);*/

    _window->clear();
    _renderer->Clear();

    _level->DrawBack(*this, _player->GetView());
    _entityManager->Draw(*this);
    _player->Draw(*this);
    _particleManager->Draw(*this);
    _level->DrawFront(*this);

    _renderer->GetTexture().setView(_renderer->GetTexture().getDefaultView());
    _gui->Draw(*this);
    _renderer->GetTexture().setView(_player->GetView());

    _renderer->DrawToWindow(*_window);
    _window->display();
}
