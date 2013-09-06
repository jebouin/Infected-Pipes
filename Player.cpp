#include "Player.h"
#include "IP.h"
#include "Character.h"
#include "Renderer.h"
#include "Map.h"
#include "MathHelper.h"

Player::Player(IP& ip, EntityManager& eManager) {
    _character = new Character(ip);
    _character->setPosition(sf::Vector2f(32, 32));
    _view = new sf::View(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
}

Player::~Player() {
    delete _view;
    delete _character;
}

void Player::Update(IP& ip, float eTime, Map& map, EntityManager& eManager) {
    float speed = 0.0005f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _character->GoRight(eTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        _character->GoLeft(eTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        _character->Jump(map);
    }

    _character->Update(ip, eTime, map, eManager);
    _view->setCenter(_character->getPosition());

    sf::FloatRect vrect = MathHelper::View2Rect(*_view);
    if(vrect.left < 16) {
        _view->setCenter(sf::Vector2f(_view->getSize().x/2.f+16, _view->getCenter().y));
    }
    if(vrect.left+vrect.width > map.GetSize().x*16.f-16) {
        _view->setCenter(sf::Vector2f(map.GetSize().x*16.f - _view->getSize().x/2.f - 16, _view->getCenter().y));
    }
    if(vrect.top < 0) {
        _view->setCenter(sf::Vector2f(_view->getCenter().x, _view->getSize().y/2.f));
    }
    if(vrect.top+vrect.height > map.GetSize().y*16.f) {
        _view->setCenter(sf::Vector2f(_view->getCenter().x, map.GetSize().y*16.f - _view->getSize().y/2.f));
    }

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
