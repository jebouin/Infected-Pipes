#include "SkillIcon.h"
#include "IP.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "MathHelper.h"

SkillIcon::SkillIcon(IP& ip, sf::Vector2i skillPos, string name, string description)
    : sf::Sprite(ResourceLoader::GetTexture("skillIcons")) {
    setTextureRect(sf::IntRect(0, 0, 16, 16));
    setOrigin(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height)/2.f);
    _content.setTexture(ResourceLoader::GetTexture("skillIcons"));
    _content.setTextureRect(sf::IntRect(skillPos.x, skillPos.y, 16, 16));
    _content.setOrigin(sf::Vector2f(_content.getGlobalBounds().width, _content.getGlobalBounds().height)/2.f);

    _name = name;
    _description = description;

    _nameText.setFont(ip._font);
    _nameText.setColor(sf::Color(200, 200, 200));
    _nameText.setString(_name);
    _nameText.setCharacterSize(8);
    _nameText.setOrigin(sf::Vector2f(_nameText.getGlobalBounds().width/2.f, _nameText.getGlobalBounds().height));

    _descriptionText.setFont(ip._font);
    _descriptionText.setColor(sf::Color(160, 160, 160));
    _descriptionText.setString(_description);
    _descriptionText.setCharacterSize(8);
    _descriptionText.setOrigin(sf::Vector2f(_descriptionText.getGlobalBounds().width/2.f, _descriptionText.getGlobalBounds().height));

    vector<sf::Vector2f> c(MathHelper::Rect2Corners(sf::FloatRect(0, 0,
                                                                  max(_nameText.getGlobalBounds().width+1, _descriptionText.getGlobalBounds().width+1),
                                                                  _nameText.getGlobalBounds().height+_descriptionText.getGlobalBounds().height+2)));
    const sf::Vector2f arrowSize(8, 8);
    sf::Vector2f centerDown((c[2]+c[3])/2.f);
    _textBox.setPointCount(7);
    _textBox.setPoint(0, sf::Vector2f(c[0]));
    _textBox.setPoint(1, sf::Vector2f(c[1]));
    _textBox.setPoint(2, sf::Vector2f(c[2]));
    _textBox.setPoint(3, centerDown + sf::Vector2f(arrowSize.x/2.f, 0));
    _textBox.setPoint(4, centerDown + sf::Vector2f(0, arrowSize.y));
    _textBox.setPoint(5, centerDown + sf::Vector2f(-arrowSize.x/2.f, 0));
    _textBox.setPoint(6, sf::Vector2f(c[3]));
    _textBox.setOutlineColor(sf::Color(255, 200, 0));
    _textBox.setOutlineThickness(1);
    _textBox.setFillColor(sf::Color(0, 0, 0, 255));
    _textBox.setOrigin(sf::Vector2f(_textBox.getGlobalBounds().width/2.f, _textBox.getGlobalBounds().height));
}

SkillIcon::~SkillIcon() {

}

void SkillIcon::Update(IP& ip, float eTime) {
    sf::Vector2f mPos(sf::Vector2f(sf::Mouse::getPosition(*ip._window))/4.f);
    if(getGlobalBounds().contains(mPos)) {
        if(_hover == false) {
            _textBoxTimer.restart();
            _hover = true;
        }
    } else {
        _hover = false;
    }
    float textBoxTime(_textBoxTimer.getElapsedTime().asMilliseconds());
    float intx = 1.f - pow(1.f - textBoxTime/200, 2);
    float b = 255;
    if(textBoxTime < 200) {
        b = intx*255.f;
    }
    _textBox.setFillColor(sf::Color(_textBox.getFillColor().r, _textBox.getFillColor().g, _textBox.getFillColor().b, b));
    _textBox.setOutlineColor(sf::Color(_textBox.getOutlineColor().r, _textBox.getOutlineColor().g, _textBox.getOutlineColor().b, b));
    if(textBoxTime < 200) {
        _textBox.setPosition(sf::Vector2f(sf::Vector2i(getPosition() + sf::Vector2f(0, -intx*16.f + 6.f))));
    } else {
        _textBox.setPosition(sf::Vector2f(sf::Vector2i(getPosition() + sf::Vector2f(0, -16.f + 6.f))));
    }
    _nameText.setPosition(_textBox.getPosition() + sf::Vector2f(-1, -_textBox.getGlobalBounds().height+4));
    _descriptionText.setPosition(_textBox.getPosition() + sf::Vector2f(-1, -14));

    if(_hover) {
        setTextureRect(sf::IntRect(0, 17, 16, 16));
    } else {
        setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    _content.setPosition(getPosition());
}

void SkillIcon::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_content);
    if(_hover) {
        ip._renderer->Draw(_textBox);
        ip._renderer->Draw(_nameText);
        ip._renderer->Draw(_descriptionText);
    }
}
