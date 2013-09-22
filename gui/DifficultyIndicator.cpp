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
    _commentText.setColor(sf::Color(92, 127, 137));

    _nbText.setFont(ip._font);
    _nbText.setCharacterSize(16);
    _nbText.setColor(sf::Color(177, 155, 165));

    _curCommentID = 0;
    _comments[0] = Comment{"Casual", 0};
    _comments[1] = Comment{"Beginner", 20};
    _comments[2] = Comment{"Easy", 42};
    _comments[3] = Comment{"Interesting", 100};
    _comments[4] = Comment{"Hard", 420};
    _comments[5] = Comment{"Hardcore", 1000};
    _comments[6] = Comment{"Insaaane!", 6666};
    _comments[7] = Comment{"PGM", 10000};
    _comments[8] = Comment{"GOD", 14159};
    _comments[9] = Comment{"O.o", 66666};
    _comments[10] = Comment{"...!", 123456};
    _comments[11] = Comment{"!!!", 987654};
}

DifficultyIndicator::~DifficultyIndicator() {

}

void DifficultyIndicator::Update(IP& ip) {
    _nbText.setString(MathHelper::IntToString(_level.GetDifficulty()));
    _nbText.setOrigin(sf::Vector2f(_nbText.getGlobalBounds().width, _nbText.getGlobalBounds().height) / 2.f);
    _nbText.setPosition(getPosition() + sf::Vector2f(getGlobalBounds().width/2.f, getGlobalBounds().height/2.f - 5));

    if(_curCommentID < 11) {
        if(_level.GetDifficulty() >= _comments[_curCommentID+1]._dif) {
            _curCommentID++;
        }
    }
    _commentText.setString(_comments[_curCommentID]._text);
    _commentText.setPosition(getPosition()
                              + sf::Vector2f(getTextureRect().width, getTextureRect().height)
                              - sf::Vector2f(_commentText.getGlobalBounds().width, _commentText.getGlobalBounds().height)
                              + sf::Vector2f(0, -3));
}

void DifficultyIndicator::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_difficultyText);
    ip._renderer->Draw(_commentText);
    ip._renderer->Draw(_nbText);
}
