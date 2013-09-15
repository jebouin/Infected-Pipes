#include "Map.h"
#include "IP.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "MovingSprite.h"

Map::Map(IP& ip, sf::Vector2i size) {
    _tileset.setTexture(ip._textureLoader->GetTexture("tileset"));
    _size = size;
    _tiles = vector<vector<int> >(_size.x, vector<int>(_size.y, 0));
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
}

Map::~Map() {

}

void Map::Draw(IP& ip) {
    for(int i=0 ; i<_size.x ; i++) {
        for(int j=0 ; j<_size.y ; j++) {
            sf::Vector2i pos(i, j);
            int tileX = 0;
            int tileId = GetTile(pos);
            if(tileId == 1) {
                if(GetTile(sf::Vector2i(pos.x, pos.y-1)) == 0) {
                    tileX = 1;
                    if(GetTile(sf::Vector2i(pos.x+1, pos.y-1)) == 1) {
                        tileX = 3;
                    } else if(GetTile(sf::Vector2i(pos.x-1, pos.y-1)) == 1) {
                        tileX = 2;
                    }
                }
            }

            if(tileId == 2 || tileId == 3) {
                tileX = GetNbDirNeigboursCode(pos);
            }

            _tileset.setPosition(sf::Vector2f(i, j)*16.f);
            _tileset.setTextureRect(sf::IntRect(tileX*16, GetTile(pos)*16, 16, 16));
            ip._renderer->Draw(_tileset);
        }
    }
}

bool Map::IsOnMap(sf::Vector2i pos) {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < _size.x && pos.y < _size.y);
}

int Map::GetTile(sf::Vector2i pos) {
    if(!IsOnMap(pos)) {
        return 1;
    }
    return _tiles[pos.x][pos.y];
}

sf::Vector2i Map::GetSize() {
    return _size;
}

int Map::GetNbNeighbours(sf::Vector2i pos) {
    static sf::Vector2i dirs[8] = {sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(1, -1), sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, 1), sf::Vector2i(1, 1)};
    int nb=0, id=GetTile(pos);
    for(int i=0 ; i<8 ; i++) {
        if(GetTile(pos+dirs[i]) == id) {
            nb++;
        }
    }
    return nb;
}

int Map::GetNbDirNeigboursCode(sf::Vector2i pos) {
    static sf::Vector2i dirs[4] = {sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0)};
    int nb=0, id=_tileTypes[GetTile(pos)];
    for(int i=0 ; i<4 ; i++) {
        if(_tileTypes[GetTile(pos+dirs[i])] == id) {
            nb+=pow(2, i);
        }
    }
    return nb;
}

void Map::SetTile(sf::Vector2i pos, int id) {
    if(!IsOnMap(pos)) {
        return;
    }
    _tiles[pos.x][pos.y] = id;
}

bool Map::IsCollided(sf::FloatRect rect, TileType type) {
    vector<sf::Vector2f> corners = MathHelper::Rect2Corners(rect);
    for(float i=corners[0].x ; i<corners[1].x ; i+=8) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(i, corners[0].y)/16.f))] == type) {
            return true;
        }
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(i, corners[2].y)/16.f))] == type) {
            return true;
        }
    }
    for(float i=corners[0].y ; i<corners[2].y ; i+=8) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[0].x, i)/16.f))] == type) {
            return true;
        }
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[2].x, i)/16.f))] == type) {
            return true;
        }
    }
    if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[2])/16.f))] == type) {
        return true;
    }
    return false;
}

bool Map::IsCollided(MovingSprite& sprite, sf::Vector2f pos, TileType type) {
    return IsCollided(sf::FloatRect(sf::Vector2f(sprite.GetHitbox().left, sprite.GetHitbox().top)+pos, sf::Vector2f(sprite.GetHitbox().width, sprite.GetHitbox().height)), type);
}

bool Map::IsCollided(MovingSprite& sprite, TileType type) {
    return IsCollided(sprite.GetGlobalHitbox(), type);
}

bool Map::IsOnTileType(MovingSprite& sprite, TileType type) {
    sf::FloatRect rect = sprite.GetGlobalHitbox();
    for(float i=0 ; i<rect.width ; i+=8) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(rect.left+i, rect.top+rect.height+1)/16.f))] == type) {
            return true;
        }
    }
    if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(rect.left+rect.width, rect.top+rect.height+1)/16.f))] == type) {
        return true;
    }
    return false;
}
