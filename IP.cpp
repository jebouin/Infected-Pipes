#include "IP.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Level.h"
#include "EntityManager.h"
#include "Player.h"
#include "Background.h"
#include "ParticleManager.h"
#include "GUI.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Game.h"
#include "MathHelper.h"

IP::IP() {
    //_window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "Infected Pipes");
    _window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Infected Pipes", sf::Style::None);
    _window->setVerticalSyncEnabled(true);
    _window->setFramerateLimit(60);
    _window->setMouseCursorVisible(false);
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f));
    _sceneManager = new SceneManager(*this);

    _font.loadFromFile("font/font.ttf");
    for(int i=0 ; i<10 ; i++) {
        const sf::Glyph& g(_font.getGlyph('0'+i, 10, false));
    }
    const_cast<sf::Texture&>(_font.getTexture(8)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(16)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(32)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(48)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(64)).setSmooth(false);

    _textureLoader = new TextureLoader(*this);
    _window->setActive(true);
    _sceneManager->AddScene(new Game(*this));
    _focused = true;

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window->close();
            }
            if(e.type == sf::Event::LostFocus) {
                _focused = false;
            }
            if(e.type == sf::Event::GainedFocus) {
                _focused = true;
                _clock.restart();
            }
            if(e.type == sf::Event::Resized) {
                _clock.restart();
            }
        }

        Update();
        Draw();
    }
}

IP::~IP() {
    delete _window;
    _window = 0;
    delete _renderer;
    _renderer = 0;
    delete _textureLoader;
    _textureLoader = 0;
    delete _sceneManager;
    _sceneManager = 0;
}

void IP::Update() {
    float eTime = _clock.restart().asMilliseconds();
    if(eTime > 1000.f/30.f) {
        eTime = 1000.f/30.f;
    }
    _sceneManager->Update(eTime, *this);
    if(_sceneManager->GetNbScenes() < 1) {
        _window->close();
    }
}

void IP::Draw() {
    _window->clear();
    _renderer->Clear();

    _sceneManager->Draw(*this);

    _renderer->DrawToWindow(*_window);
    _window->display();
}
