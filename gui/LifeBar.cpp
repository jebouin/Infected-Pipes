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
    setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2, 1));

    _bar.setTexture(tLoader.GetTexture("lifeBar"));
    _bar.setOrigin(sf::Vector2f(40, 0));
    _bar.setPosition(getPosition());

    _text.setFont(ip._font);
    _text.setCharacterSize(8);
}

LifeBar::~LifeBar() {

}

void LifeBar::Update(IP& ip) {
    float hp = _character.GetHP();
    float hpm = _character.GetHPMax();
    _bar.setTextureRect(sf::IntRect(0, 0, hp*80/hpm, 8));

    _text.setString(MathHelper::IntToString(hp) + "/" + MathHelper::IntToString(hpm));
    _text.setOrigin(sf::Vector2f(sf::Vector2i(_text.getGlobalBounds().width, _text.getGlobalBounds().height) / 2));
    _text.setPosition(sf::Vector2f(sf::Vector2i(getPosition().x, getPosition().y+2)));
    HSV c{hp/hpm*25.f, (1.-hp/hpm)*100., 50.f + 50.f*(1.-(hp/hpm))};
    _text.setColor(MathHelper::HSVToRGB(c));
}

void LifeBar::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_bar);
    ip._renderer->Draw(_text);
}
