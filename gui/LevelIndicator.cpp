#include "LevelIndicator.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

LevelIndicator::LevelIndicator(IP& ip, Character& character, TextureLoader& tLoader)
    : sf::Sprite(), _character(character) {
    setTexture(tLoader.GetTexture("levelIndicator"));
    setPosition(sf::Vector2f(1, 1));

    _levelText.setFont(ip._font);
    _levelText.setCharacterSize(8);
    _levelText.setPosition(getPosition() + sf::Vector2f(2, -1));
    _levelText.setString("Level");
    _levelText.setColor(sf::Color(92, 127, 137));

    _nbText.setFont(ip._font);
    _nbText.setCharacterSize(16);
    _nbText.setColor(sf::Color(177, 155, 165));
}

LevelIndicator::~LevelIndicator() {

}

void LevelIndicator::Update(IP& ip) {
    _nbText.setString(MathHelper::IntToString(_character.GetLevel()));
    _nbText.setOrigin(sf::Vector2f(_nbText.getGlobalBounds().width, _nbText.getGlobalBounds().height) / 2.f);
    _nbText.setPosition(getPosition() + sf::Vector2f(getGlobalBounds().width/2.f, 8));
}

void LevelIndicator::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_levelText);
    ip._renderer->Draw(_nbText);
}
