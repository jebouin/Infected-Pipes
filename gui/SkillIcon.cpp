#include "SkillIcon.h"
#include "IP.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "MathHelper.h"
#include "Skill.h"

SkillIcon::SkillIcon(IP& ip, sf::Vector2i skillPos, string name, string description, Skill& skill)
    : sf::Sprite(ResourceLoader::GetTexture("skillIcons")), _skill(skill) {
    setTextureRect(sf::IntRect(0, 0, 16, 16));
    setOrigin(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height)/2.f);
    _content.setTexture(ResourceLoader::GetTexture("skillIcons"));
    _content.setTextureRect(sf::IntRect(skillPos.x, skillPos.y, 16, 16));
    _content.setOrigin(sf::Vector2f(_content.getGlobalBounds().width, _content.getGlobalBounds().height)/2.f);
    _skillPos = skillPos;

    _name = name;
    _description = description;
    _hidden = true;
    _clicked = false;
    _hover = false;
    _doubleClicked = false;
    _canDoubleClick = false;
    _canClick = false;

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

    _levelText.setFont(ip._font);
    _levelText.setColor(sf::Color(180, 90, 0));
    _levelText.setCharacterSize(8);

    _doubleClickText.setFont(ip._font);
    _doubleClickText.setCharacterSize(8);
    _doubleClickText.setString("Click again!");
    _doubleClickText.setOrigin(sf::Vector2f(_doubleClickText.getGlobalBounds().width/2.f, 0));

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

    c = MathHelper::Rect2Corners(sf::FloatRect(0, 0, _doubleClickText.getGlobalBounds().width, _doubleClickText.getGlobalBounds().height+2));
    sf::Vector2f centerUp = sf::Vector2f((c[0]+c[1])/2.f);
    _doubleClickBox.setPointCount(7);
    _doubleClickBox.setPoint(0, sf::Vector2f(c[0]));
    _doubleClickBox.setPoint(1, sf::Vector2f(c[3]));
    _doubleClickBox.setPoint(2, sf::Vector2f(c[2]));
    _doubleClickBox.setPoint(3, sf::Vector2f(c[1]));
    _doubleClickBox.setPoint(4, centerUp + sf::Vector2f(arrowSize.x/2.f, 0));
    _doubleClickBox.setPoint(5, centerUp + sf::Vector2f(0, -arrowSize.y));
    _doubleClickBox.setPoint(6, centerUp + sf::Vector2f(-arrowSize.x/2.f, 0));
    _doubleClickBox.setOutlineColor(sf::Color(255, 200, 0));
    _doubleClickBox.setOutlineThickness(1);
    _doubleClickBox.setFillColor(sf::Color(0, 0, 0, 255));
    _doubleClickBox.setOrigin(sf::Vector2f(_doubleClickBox.getGlobalBounds().width/2.f, 0));
}

SkillIcon::~SkillIcon() {

}

void SkillIcon::Update(IP& ip, float eTime) {
    sf::Vector2f mPos(ip._renderer->GetTexture().mapPixelToCoords(sf::Mouse::getPosition(*ip._window)/4));
    if(_hidden) {
        _content.setTextureRect(sf::IntRect(16, 0, 16, 16));
    } else {
        _content.setTextureRect(sf::IntRect(_skillPos.x, _skillPos.y, 16, 16));
        if(getGlobalBounds().contains(mPos)) {
            if(_hover == false) {
                _textBoxTimer.restart();
                _hover = true;
            }
        } else {
            _hover = false;
            _clicked = false;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(_hover) {
                if(!_clicked && _skill.GetLevel() < _skill.GetLevelMax() && _canClick) {
                    _doubleClickTimer.restart();
                    _clicked = true;
                    _canDoubleClick = false;
                } else {
                    if(_canDoubleClick) {
                        _doubleClicked = true;
                        _canDoubleClick = false;
                        _clicked = false;
                        _canClick = false;
                    }
                }
            } else {
                _clicked = false;
                _doubleClicked = false;
                _canDoubleClick = false;
            }
        } else {
            _doubleClicked = false;
            if(_clicked) {
                _canDoubleClick = true;
            } else {
                _canClick = true;
            }
        }

        float textBoxTime(_textBoxTimer.getElapsedTime().asMilliseconds());
        float intx = 1.f - pow(1.f - textBoxTime/200, 2);
        float b = 255;
        if(textBoxTime < 200) {
            b = intx*255.f;
        }
        _textBox.setFillColor(sf::Color(_textBox.getFillColor().r, _textBox.getFillColor().g, _textBox.getFillColor().b, b));
        _textBox.setOutlineColor(sf::Color(_textBox.getOutlineColor().r, _textBox.getOutlineColor().g, _textBox.getOutlineColor().b, b));
        _nameText.setColor(sf::Color(_nameText.getColor().r, _nameText.getColor().g, _nameText.getColor().b, b));
        _descriptionText.setColor(sf::Color(_descriptionText.getColor().r, _descriptionText.getColor().g, _descriptionText.getColor().b, b));
        if(textBoxTime < 200) {
            _textBox.setPosition(sf::Vector2f(sf::Vector2i(getPosition() + sf::Vector2f(0, -intx*16.f + 6.f))));
        } else {
            _textBox.setPosition(sf::Vector2f(sf::Vector2i(getPosition() + sf::Vector2f(0, -16.f + 6.f))));
        }
        _nameText.setPosition(_textBox.getPosition() + sf::Vector2f(-1, -_textBox.getGlobalBounds().height+4));
        _descriptionText.setPosition(_textBox.getPosition() + sf::Vector2f(-1, -14));

        //double click text and box
        float doubleClickTime(_doubleClickTimer.getElapsedTime().asMilliseconds());
        intx = 1.f - pow(1.f - doubleClickTime/200, 2);
        b = 255;
        if(doubleClickTime < 200) {
            b = intx*255.f;
        }
        sf::Color tc(int(doubleClickTime)%200<100 ? sf::Color(255, 255, 0) : sf::Color(180, 90, 20));
        _doubleClickText.setColor(sf::Color(tc.r, tc.g, tc.b, b));
        _doubleClickBox.setFillColor(sf::Color(_doubleClickBox.getFillColor().r, _doubleClickBox.getFillColor().g, _doubleClickBox.getFillColor().b, b));
        _doubleClickBox.setOutlineColor(sf::Color(tc.r, tc.g, tc.b, b));
        if(doubleClickTime < 200) {
            _doubleClickBox.setPosition(sf::Vector2f(getPosition() + sf::Vector2f(0, intx*16 + 8)));
        } else {
            _doubleClickBox.setPosition(sf::Vector2f(getPosition() + sf::Vector2f(0, 16 + 8)));
        }
        _doubleClickText.setPosition(_doubleClickBox.getPosition() + sf::Vector2f(0, -2));

        //level text
        int level(_skill.GetLevel());
        int levelMax(_skill.GetLevelMax());
        if(level == 0) {
            _levelText.setColor(sf::Color(100, 100, 100));
        } else if(level == levelMax) {
            _levelText.setColor(sf::Color(200, 200, 0));
        } else {
            _levelText.setColor(sf::Color(175, 90, 0));
        }
        _levelText.setString(MathHelper::IntToString(_skill.GetLevel()) + "/" + MathHelper::IntToString(_skill.GetLevelMax()));
        _levelText.setOrigin(sf::Vector2f(_levelText.getGlobalBounds().width/2.f, 0));
        _levelText.setPosition(getPosition()+sf::Vector2f(0, 6));

        if(_hover) {
            setTextureRect(sf::IntRect(0, 16, 16, 16));
        } else {
            setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
    }

    _content.setPosition(getPosition());
}

void SkillIcon::DrawBack(IP& ip) {
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_content);
    if(!_hidden) {
        ip._renderer->Draw(_levelText);
    }
}

void SkillIcon::DrawTop(IP& ip) {
    if(_hover && !_hidden) {
        ip._renderer->Draw(_textBox);
        ip._renderer->Draw(_nameText);
        ip._renderer->Draw(_descriptionText);
    }
    if(_clicked) {
        ip._renderer->Draw(_doubleClickBox);
        ip._renderer->Draw(_doubleClickText);
    }
}

void SkillIcon::Unhide() {
    _hidden = false;
}

bool SkillIcon::IsClicked() {
    return _clicked;
}

bool SkillIcon::IsDoubleClicked() {
    if(_doubleClicked) {
        _doubleClicked = false;
        return true;
    }
    return false;
}
