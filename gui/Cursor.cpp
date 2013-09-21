#include "Cursor.h"
#include "IP.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

Cursor::Cursor(IP& ip, TextureLoader& tLoader) : sf::Sprite() {
    setTexture(tLoader.GetTexture("cursor"));
    _prevPos = getPosition();
}

Cursor::~Cursor() {

}

void Cursor::Update(IP& ip) {
    setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(sf::Mouse::getPosition(*(ip._window))) / 4.f)));

    if(MathHelper::GetVecLength(_prevPos-getPosition()) > 1) {
        _inactiveTimer.restart();
        setColor(sf::Color(getColor().r, getColor().g, getColor().b, 255));
    } else {
        float t = _inactiveTimer.getElapsedTime().asMilliseconds();
        if(t >= 2000 && t <= 3000) {
            setColor(sf::Color(getColor().r, getColor().g, getColor().b, 255-256*((t-2000.) / 1000.)));
        }
    }

    _prevPos = getPosition();
}

void Cursor::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}
