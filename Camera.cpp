#include "Camera.h"
#include "IP.h"
#include "Character.h"
#include "Player.h"
#include "Level.h"
#include "Map.h"
#include "mathHelper.h"

Camera::Camera(sf::FloatRect size) : sf::View(size) {

}

Camera::~Camera() {

}

void Camera::Update(IP& ip, float eTime, Level& level, Character& character) {
    setCenter(character.getPosition() + sf::Vector2f(100.f, 0));
    Map& map(level.GetMap());
    sf::FloatRect vrect = MathHelper::View2Rect(*this);
    if(vrect.left < 16) {
        setCenter(sf::Vector2f(getSize().x/2.f+16, getCenter().y));
    }
    if(vrect.left+vrect.width > map.GetSize().x*16.f-16) {
        setCenter(sf::Vector2f(map.GetSize().x*16.f - getSize().x/2.f - 16, getCenter().y));
    }
    if(vrect.top < 0) {
        setCenter(sf::Vector2f(getCenter().x, getSize().y/2.f));
    }
    if(vrect.top+vrect.height > map.GetSize().y*16.f) {
        setCenter(sf::Vector2f(getCenter().x, map.GetSize().y*16.f - getSize().y/2.f));
    }

    setCenter(sf::Vector2f(sf::Vector2i(getCenter())));
}
