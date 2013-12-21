#include "WaveIndicator.h"
#include "IP.h"
#include "ResourceLoader.h"
#include "Level.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "MovingSprite.h"

WaveIndicator::WaveIndicator(IP& ip) {
    _text.setFont(ip._font);
    _text.setColor(sf::Color(200, 120, 20));
    _text.setCharacterSize(48);
    _text.setPosition(sf::Vector2f(0, 0));
    _top = 0;
    _bottom = 0;
    _speed = 1.8f;
    _announcing = false;
    _passed = false;
    _rt.create(220, 60, false);
}

WaveIndicator::~WaveIndicator() {
    delete _top;
    _top = 0;
    delete _bottom;
    _bottom = 0;
}

void WaveIndicator::Update(IP& ip, float eTime) {
    if(_announcing) {
        _top->move(eTime*_speed, 0);
        _bottom->move(eTime*-_speed, 0);

        if(_bottom->getPosition().x - 3 < _top->getPosition().x && !_passed) {
            _bottom->setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2.f + 3 , _bottom->getPosition().y));
            _top->setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2.f - 3, _top->getPosition().y));
            _passed = true;
            _speed = .01f;
        } else if(_passed && _bottom->getPosition().x + 4 < _top->getPosition().x) {
            _speed = 1.8f;
        }

        if(_text.getString() == "BOSS") {
            _bottom->setColor(sf::Color(255, (int)((sin(_timer.getElapsedTime().asSeconds()*32.f)+1.f)*127.f), 20));
        } else {
            _bottom->setColor(sf::Color(200, 120, 20));
        }
        _top->setColor(_bottom->getColor());

        if(_timer.getElapsedTime().asSeconds() >= 5.f) {
            _announcing = false;
            delete _top;
            delete _bottom;
        }
    }
}

void WaveIndicator::Draw(IP& ip) {
    if(_announcing) {
        ip._renderer->Draw(*_top);
        ip._renderer->Draw(*_bottom);
    }
}

void WaveIndicator::AnnounceWave(IP& ip, int nb) {
    _announcing = true;
    _passed = false;
    _timer.restart();
    if(nb != -42) {
        _text.setString("Wave " + MathHelper::IntToString(nb));
    } else {
        _text.setString("BOSS");
    }

    _rt.clear(sf::Color(0, 0, 0, 0));
    _rt.draw(_text);
    _rt.display();

    sf::IntRect ts(_text.getGlobalBounds());

    _top = new sf::Sprite();
    _bottom = new sf::Sprite();
    _top->setTexture(_rt.getTexture());
    _bottom->setTexture(_rt.getTexture());

    _bottom->setTextureRect(sf::IntRect(0, ts.height, ts.width, ts.height/2));
    _bottom->setOrigin(sf::Vector2f(_bottom->getTextureRect().width, _bottom->getTextureRect().height)/2.f);
    _bottom->setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(ip._renderer->GetTexture().getSize().x +_bottom->getGlobalBounds().width, float(ip._renderer->GetTexture().getSize().y)/2.f + _bottom->getGlobalBounds().height/2.f))));

    _top->setTextureRect(sf::IntRect(0, ts.height/2, ts.width, ts.height/2));
    _top->setOrigin(sf::Vector2f(_top->getTextureRect().width, _top->getTextureRect().height)/2.f);
    _top->setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(-_top->getGlobalBounds().width, float(ip._renderer->GetTexture().getSize().y)/2.f - _top->getGlobalBounds().height/2.f))));
}
