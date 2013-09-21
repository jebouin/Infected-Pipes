#include "LifeBar.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

LifeBar::LifeBar(IP& ip, Character& character, TextureLoader& tLoader) :
    sf::Sprite(), _character(character) {
    setTexture(tLoader.GetTexture("lifeBarBorder"));
    setOrigin(sf::Vector2f(40, 0));
    setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2.f, 1.));

    _bar.setTexture(tLoader.GetTexture("lifeBar"));
    _bar.setOrigin(sf::Vector2f(40, 0));
    _bar.setPosition(getPosition());

    const_cast<sf::Texture&>(ip._font.getTexture(8)).setSmooth(false);
    _text.setFont(ip._font);
    _text.setCharacterSize(8);
}

LifeBar::~LifeBar() {

}

void LifeBar::Update(IP& ip) {
    float hp = _character.GetHp();
    float hpm = _character.GetHpMax();
    _bar.setTextureRect(sf::IntRect(0, 0, hp*80/hpm, 8));

    _text.setString(MathHelper::IntToString(hp) + "/" + MathHelper::IntToString(hpm));
    _text.setOrigin(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height)/2.f);
    _text.setPosition(sf::Vector2f(getPosition().x, getPosition().y+2));
}

void LifeBar::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_bar);
    ip._renderer->Draw(_text);
}
