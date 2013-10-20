#include "SpeechBubble.h"
#include "IP.h"
#include "GameEntity.h"
#include "Renderer.h"
#include "MathHelper.h"

SpeechBubble::SpeechBubble(IP& ip, string text, const GameEntity& speaker, float stayTime, float fadeTime)
    : sf::ConvexShape(), _speaker(speaker){
    _stayTime = stayTime;
    _fadeTime = fadeTime;

    _alive = true;
    _fading = false;

    //text
    _text.setFont(ip._font);
    _text.setCharacterSize(8);
    _text.setColor(sf::Color(92, 127, 137));
    _text.setString(text);

    //shape
    setOutlineThickness(1);
    setOutlineColor(sf::Color(92, 127, 137));
    setFillColor(sf::Color(33, 33, 33));
    setPointCount(7);
    sf::FloatRect rect = sf::FloatRect(_text.getGlobalBounds().left, _text.getGlobalBounds().top, _text.getGlobalBounds().width+1, _text.getGlobalBounds().height+1);
    sf::Vector2f arrowSize(4, 4);
    vector<sf::Vector2f> corners = MathHelper::Rect2Corners(rect);
    float midWidthPos = (corners[0].x+corners[1].x)/2.f;
    setPoint(0, corners[0]);
    setPoint(1, corners[1]);
    setPoint(2, corners[2]);
    setPoint(3, sf::Vector2f(midWidthPos+arrowSize.x/2.f, corners[2].y));
    setPoint(4, sf::Vector2f(midWidthPos, corners[2].y+arrowSize.y));
    setPoint(5, sf::Vector2f(midWidthPos-arrowSize.x/2.f, corners[2].y));
    setPoint(6, corners[3]);

    _text.setOrigin(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height)/2.f);
    _upperRect = rect;
}

SpeechBubble::~SpeechBubble() {

}

void SpeechBubble::Update(IP& ip, float eTime) {
    setPosition(sf::Vector2f(sf::Vector2i(sf::Vector2f(_speaker.getPosition().x-getGlobalBounds().width/2.f, _speaker.getGlobalBounds().top-getGlobalBounds().height) + sf::Vector2f(0, -5))));
    _text.setPosition(sf::Vector2f(sf::Vector2i(getPosition() + MathHelper::GetCenter(_upperRect) + sf::Vector2f(1, -2))));

    if(_alive) {
        if(!_fading) {
            if(_timer.getElapsedTime().asMilliseconds() >= _stayTime) {
                _timer.restart();
                _fading = true;
            }
        } else {
            float alpha = 255-255*(_timer.getElapsedTime().asMilliseconds()/_fadeTime);
            setOutlineColor(sf::Color(getOutlineColor().r, getOutlineColor().g, getOutlineColor().b, alpha));
            setFillColor(sf::Color(getFillColor().r, getFillColor().g, getFillColor().b, alpha));
            _text.setColor(sf::Color(_text.getColor().r, _text.getColor().g, _text.getColor().b, alpha));
            if(_timer.getElapsedTime().asMilliseconds() >= _fadeTime) {
                _timer.restart();
                _alive = false;
                _fading = false;
                setOutlineColor(sf::Color(getOutlineColor().r, getOutlineColor().g, getOutlineColor().b, 0));
                setFillColor(sf::Color(getFillColor().r, getFillColor().g, getFillColor().b, 0));
                _text.setColor(sf::Color(_text.getColor().r, _text.getColor().g, _text.getColor().b, 0));
            }
        }
    }
}

void SpeechBubble::Draw(IP& ip){
    ip._renderer->Draw(*this);
    ip._renderer->Draw(_text);
}

bool SpeechBubble::IsAlive() {
    return _alive;
}
