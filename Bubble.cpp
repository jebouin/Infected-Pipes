#include "Bubble.h"
#include "IP.h"
#include "Level.h"
#include "Map.h"
#include "ResourceLoader.h"
#include "Renderer.h"
#include "MathHelper.h"

Bubble::Bubble(IP& ip, Map& map)
    : sf::Sprite(ResourceLoader::GetTexture("bubble")) {
    _alive = true;
    setOrigin(sf::Vector2f(2, 2));
    sf::Vector2i tpos(0, 0);
    while(map.GetTile(tpos, Map::FRONT) != 0 || map.GetTileType(tpos+sf::Vector2i(0, 1), Map::FRONT) != Map::WALL) {
        tpos = sf::Vector2i(MathHelper::RandInt(0, map.GetSize().x), MathHelper::RandInt(0, map.GetSize().y));
    }
    setPosition(sf::Vector2f(tpos*16) + sf::Vector2f(MathHelper::RandInt(1, 15), 14));
    setColor(sf::Color(255, 255, 255, MathHelper::RandFloat(80, 120)));
    _relPos = getPosition();
    _timer = MathHelper::RandFloat(0, 2000);
}

Bubble::~Bubble() {

}

void Bubble::Update(IP& ip, float eTime, Level& level) {
    _timer += eTime;
    _relPos += sf::Vector2f(0, -.01*eTime);
    setPosition(_relPos);
    if(level.GetMap().GetTileType(sf::Vector2i(getPosition()/16.f), Map::FRONT) == Map::WALL) {
        _alive = false;
    }
    setPosition(_relPos + sf::Vector2f(sin(_timer/3000.f*PI*2)*4, 0));
}

void Bubble::Draw(IP& ip) {
    ip._renderer->Draw(*this);
}

bool Bubble::IsAlive() {
    return _alive;
}
