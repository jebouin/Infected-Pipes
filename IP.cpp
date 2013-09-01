#include "IP.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Map.h"
#include "EntityManager.h"
#include "Player.h"

IP::IP() {
    _window = new sf::RenderWindow(sf::VideoMode(960, 680, 32), "Infected Pipes");
    _window->setVerticalSyncEnabled(true);
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f), 4);
    _textureLoader = new TextureLoader();
    _map = new Map(*this);
    _entityManager = new EntityManager();
    _player = new Player(*this, *_entityManager);

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                _window->close();
            }
            if(e.type == sf::Event::Resized) {
                _renderer = new Renderer(sf::Vector2i(sf::Vector2f(e.size.width, e.size.height)/4.f), 4);
                _player->SetView(sf::View(sf::FloatRect(0, 0, _renderer->GetTexture().getSize().x, _renderer->GetTexture().getSize().y)));
            }
        }

        Update();
        Draw();
    }
}

IP::~IP() {
    delete _window;
    delete _renderer;
    delete _textureLoader;
    delete _map;
    delete _entityManager;
    delete _player;
}

void IP::Update() {
    float eTime = _clock.restart().asMilliseconds();
    _entityManager->Update(*this, eTime, *_map);
    _player->Update(*this, eTime, *_map);
}

void IP::Draw() {
    /*sf::View v(_window->getDefaultView());  //test
    v.zoom(0.5f);
    _window->setView(v);*/

    _window->clear();
    _renderer->Clear();

    _entityManager->Draw(*this);
    _map->Draw(*this);
    _player->Draw(*this);

    _renderer->DrawToWindow(*_window);
    _window->display();
}
