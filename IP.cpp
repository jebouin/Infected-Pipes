#include "IP.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Map.h"

IP::IP() {
    _window = new sf::RenderWindow(sf::VideoMode(960, 680, 32), "Infected Pipes");
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f), 4);
    _textureLoader = new TextureLoader();
    _map = new Map(*this);

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                _window->close();
            }
            if(e.type == sf::Event::Resized) {
                //_player->SetView(sf::View(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y)));
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
}

void IP::Update() {

}

void IP::Draw() {
    /*sf::View v(_window->getDefaultView());  //test
    v.zoom(0.5f);
    _window->setView(v);*/

    _window->clear();
    _renderer->Clear();

    _map->Draw(*this);

    _renderer->DrawToWindow(*_window);
    _window->display();
}
