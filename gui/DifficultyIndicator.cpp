#include "DifficultyIndicator.h"
#include "IP.h"
#include "Level.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

DifficultyIndicator::DifficultyIndicator(IP& ip, Level& level, TextureLoader& tLoader)
    : sf::Sprite(), _level(level) {
    setTexture(tLoader.GetTexture("difficultyIndicator"));
    setPosition(sf::Vector2f(ip._renderer->GetTexture().getSize().x - getTextureRect().width - 1, 1));

    _difficultyText.setFont(ip._font);
    _difficultyText.setCharacterSize(8);
    _difficultyText.setPosition(getPosition() + sf::Vector2f(2, -1));
    _difficultyText.setString("Difficulty");
    _difficultyText.setColor(sf::Color(92, 127, 137));

    _commentText.setFont(ip._font);
    _commentText.setCharacterSize(8);
    _commentText.setString("Insaaane!");
    _commentText.setColor(sf::Color(92, 127, 137));
    _commentText.setPosition(getPosition()
                              + sf::Vector2f(getTextureRect().width, getTextureRect().height)
                              - sf::Vector2f(_commentText.getGlobalBounds().width, _commentText.getGlobalBounds().height)
                              + sf::Vector2f(0, -3));

    _nbText.setFont(ip._font);
    _nbText.setCharacterSize(16);
    _nbText.setColor(sf::Color(177, 155, 165));
}

DifficultyIndicator::~DifficultyIndicator() {

}

void DifficultyIndicator::Update(IP& ip) {
    _nbText.setString(MathHelper::IntToString(_level.GetDifficulty()));
    _nbText.setOrigin(sf::Vector2f(_nbText.getGlobalBounds().width, _nbText.getGlobalBounds().height) / 2.f);
    _nbText.setPosition(getPosition() + sf::Vector2f(getGlobalBounds().width/2.f, getGlobalBounds().height/2.f - 5));
}

void DifficultyIndicator::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_difficultyText);
    ip._renderer->Draw(_commentText);
    ip._renderer->Draw(_nbText);
}
