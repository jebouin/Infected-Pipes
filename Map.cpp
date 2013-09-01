#include "Map.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "MovingSprite.h"

Map::Map(IP& ip) {
    _tileset.setTexture(ip._textureLoader->GetTexture("tileset"));
    _size = sf::Vector2i(16, 16);
    _tiles = vector<vector<int> >(_size.x, vector<int>(_size.y, 0));
    for(int i=0 ; i<_size.x ; i++) {
        for(int j=0 ; j<_size.y ; j++) {
            SetTile(sf::Vector2i(i, j), (rand()%4==0?1:0));
        }
    }
    for(int i=0 ; i<_size.x ; i++) {
        SetTile(sf::Vector2i(i, 0), 1);
        SetTile(sf::Vector2i(i, _size.y-1), 1);
    }
    for(int i=0 ; i<_size.y ; i++) {
        SetTile(sf::Vector2i(0, i), 1);
        SetTile(sf::Vector2i(_size.x-1, i), 1);
    }
    for(int i=0 ; i<25 ; i++) {
        SetTile(sf::Vector2i(i%5+1, i/5+1), 0);
    }
}

Map::~Map() {

}

void Map::Draw(IP& ip) {
    for(int i=0 ; i<_size.x ; i++) {
        for(int j=0 ; j<_size.y ; j++) {
            _tileset.setPosition(sf::Vector2f(i, j)*16.f);
            _tileset.setTextureRect(sf::IntRect(0, GetTile(sf::Vector2i(i, j))*16, 16, 16));
            ip._renderer->Draw(_tileset);
        }
    }
}

bool Map::IsOnMap(sf::Vector2i pos) {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < _size.x && pos.y < _size.y);
}

int Map::GetTile(sf::Vector2i pos) {
    if(!IsOnMap(pos)) {
        return 0;
    }
    return _tiles[pos.x][pos.y];
}

void Map::SetTile(sf::Vector2i pos, int id) {
    if(!IsOnMap(pos)) {
        return;
    }
    _tiles[pos.x][pos.y] = id;
}

bool Map::IsCollided(sf::FloatRect rect) {
    vector<sf::Vector2f> corners = MathHelper::Rect2Corners(rect);
    for(int i=0 ; i<4 ; i++) {
        if(GetTile(sf::Vector2i(corners[i]/16.f)) == 1) {
            return true;
        }
    }
    return false;
}

bool Map::IsCollided(MovingSprite& sprite, sf::Vector2f pos) {
    return IsCollided(sf::FloatRect(pos, sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height)));
}

bool Map::IsCollided(MovingSprite& sprite) {
    return IsCollided(sprite.getGlobalBounds());
}
