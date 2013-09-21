#include "XPBar.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

XPBar::XPBar(IP& ip, Character& character, TextureLoader& tLoader) :
    sf::Sprite(), _character(character) {
    setTexture(tLoader.GetTexture("xpBarBorder"));
    setOrigin(sf::Vector2f(30, 0));
    setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x/2.f, 11.));

    _bar.setTexture(tLoader.GetTexture("xpBar"));
    _bar.setOrigin(sf::Vector2f(30, 0));
    _bar.setPosition(getPosition());
}

XPBar::~XPBar() {

}

void XPBar::Update(IP& ip) {
    float xp = _character.GetXP();
    float nxp = _character.GetNextXP();
    _bar.setTextureRect(sf::IntRect(0, 0, xp*60/nxp, 3));
}

void XPBar::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_bar);
}
