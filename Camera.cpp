#include "Camera.h"
#include "IP.h"
#include "Character.h"
#include "Player.h"
#include "Level.h"
#include "Map.h"
#include "MathHelper.h"
#include "Spawner.h"

Camera::Camera(sf::FloatRect size) : sf::View(size) {
    _nextRelPosX = 0;
    _curRelPosX = 0;
    _prevY = 0;
    zoom(1.);
}

Camera::~Camera() {

}

void Camera::Update(IP& ip, float eTime, Level& level, Character& character) {
    Map& map(level.GetMap());
    sf::Vector2f charPos = character.getPosition();

    //x
    if(character.IsInWater(level)) {
        _nextRelPosX = 0;
    }
    if(_curRelPosX > _nextRelPosX) {
        _curRelPosX -= eTime*.1f;
        if(_curRelPosX < _nextRelPosX) {
            _curRelPosX = _nextRelPosX;
        }
    }
    if(_curRelPosX < _nextRelPosX) {
        _curRelPosX += eTime*.1f;
        if(_curRelPosX > _nextRelPosX) {
            _curRelPosX = _nextRelPosX;
        }
    }
    //y
    if((level.GetSpawner().IsOnGround(character) || map.IsOnTileType(character, Map::WALL) || map.IsOnTileType(character, Map::PLATFORM)) && character.GetVel().y >= 0.) {
        _prevY = character.getPosition().y;
    }
    float ypos = getCenter().y;
    if(ypos > _prevY) {
        ypos -= eTime*.3f;
        if(ypos < _prevY) {
            ypos = _prevY;
        }
    }
    if(ypos < _prevY) {
        ypos += eTime*.3f;
        if(ypos > _prevY) {
            ypos = _prevY;
        }
    }
    if(character.IsInWater(level)) {
        _prevY = character.getPosition().y;
        ypos = 0;
    }
    if(character.getPosition().y > getCenter().y && character.GetVel().y > 0.) {
        setCenter(sf::Vector2f(getCenter().x, character.getPosition().y));
    } else {
        setCenter(sf::Vector2f(getCenter().x, ypos));
    }
    setCenter(sf::Vector2f(character.getPosition().x + _curRelPosX, getCenter().y));

    //if we are really far from the player (changed level or some teleportation, jump to the player)
    if(MathHelper::ABS(getCenter().x - character.getPosition().x) > 100 || MathHelper::ABS(getCenter().y - character.getPosition().y) > 150) {
        setCenter(character.getPosition());
    }

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

    //setCenter(sf::Vector2f(sf::Vector2i(getCenter())));
}

void Camera::Focus(Character& character) {
    setCenter(character.getPosition());
}

void Camera::GoLeft() {
    _nextRelPosX = -50;
}

void Camera::GoRight() {
    _nextRelPosX = 50;
}

void Camera::GoCenter() {
    _nextRelPosX = 0;
}
