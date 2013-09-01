#include "Player.h"
#include "IP.h"
#include "Character.h"
#include "Renderer.h"
#include "Map.h"

Player::Player(IP& ip, EntityManager& eManager) {
    _character = new Character(ip);
    _character->setPosition(sf::Vector2f(32, 32));
    _view = new sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
}

Player::~Player() {
    delete _view;
    delete _character;
}

void Player::Update(IP& ip, float eTime, Map& map) {
    float speed = 0.0005f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _character->Accelerate(sf::Vector2f(speed, 0), eTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        _character->Accelerate(sf::Vector2f(-speed, 0), eTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        _character->Accelerate(sf::Vector2f(0, -speed), eTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _character->Accelerate(sf::Vector2f(0, speed), eTime);
    }

    _character->Update(ip, eTime, map);
    _view->setCenter(_character->getPosition());
    ip._renderer->GetTexture().setView(*_view);
}

void Player::Draw(IP& ip) {
    ip._renderer->Draw(*_character);
}

sf::View& Player::GetView() {
    return *_view;
}

Character& Player::GetCharacter() {
    return *_character;
}

void Player::SetView(sf::View v) {
    _view = new sf::View(v);
}
