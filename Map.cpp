#include "Map.h"
#include "IP.h"
#include "ResourceLoader.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "MovingSprite.h"

Map::Map(IP& ip, sf::Vector2i size) {
    _tileset.setTexture(ResourceLoader::GetTexture("tileset"));
    _size = size;
    _tiles = std::vector<std::vector<std::vector<int> > >(2, std::vector<std::vector<int> >(_size.x, std::vector<int>(_size.y, 0)));
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(PLATFORM);
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(WALL);
    _tileTypes.push_back(PLATFORM);
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(VOID);
    _tileTypes.push_back(WALL);
}

Map::~Map() {

}

void Map::DrawLayer(sf::RenderTexture& rt, Layer l) {
    sf::FloatRect vrect = MathHelper::View2Rect(rt.getView());
    for(int i=vrect.left/16.f ; i<(vrect.left+vrect.width)/16.f ; i++) {
        for(int j=vrect.top/16.f ; j<(vrect.top+vrect.height)/16.f ; j++) {
            sf::Vector2i pos(i, j);
            if(!IsOnMap(pos)) {
                continue;
            }
            int tileX = 0;
            int tileId = GetTile(pos, l);
            if(tileId == 1) {
                if(GetTile(sf::Vector2i(pos.x, pos.y-1), l) == 0) {
                    tileX = 1;
                    if(GetTile(sf::Vector2i(pos.x+1, pos.y-1), l) == 1) {
                        tileX = 3;
                    } else if(GetTile(sf::Vector2i(pos.x-1, pos.y-1), l) == 1) {
                        tileX = 2;
                    }
                }
            }

            if(tileId == 2 || tileId == 3 || tileId == 6 || tileId == 9 || tileId == 10 || tileId == 11 || tileId == 15) {
                tileX = GetNbDirNeighboursCode(pos, l, false);
            }

            if(tileId == 4 || tileId == 12) {
                if(GetTile(sf::Vector2i(i+1, j), l) != tileId && GetTileType(sf::Vector2i(i+1, j), l) == Map::WALL) {
                    tileX = 2;
                } else if(GetTile(sf::Vector2i(i-1, j), l) != tileId && GetTileType(sf::Vector2i(i-1, j), l) == Map::WALL) {
                    tileX = 0;
                } else {
                    tileX = 1;
                }
            }

            if(tileId == 15) {
                if(tileX == 15) {
                    tileX = 16+GetNbDirNeighboursCode(pos, l, true);
                }
            }

            _tileset.setPosition(sf::Vector2f(i, j)*16.f);
            _tileset.setTextureRect(sf::IntRect(tileX*16, GetTile(pos, l)*16, 16, 16));
            rt.draw(_tileset);
        }
    }
}

bool Map::IsOnMap(sf::Vector2i pos) {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < _size.x && pos.y < _size.y);
}

int Map::GetTile(sf::Vector2i pos, Layer layer) {
    if(!IsOnMap(pos)) {
        return _tiles[layer][0][0];
    }
    return _tiles[layer][pos.x][pos.y];
}

int Map::GetTileType(int tileId) {
    return _tileTypes[tileId];
}

int Map::GetTileType(sf::Vector2i pos, Layer layer) {
    return GetTileType(GetTile(pos, layer));
}

sf::Vector2i Map::GetSize() {
    return _size;
}

int Map::GetNbNeighbours(sf::Vector2i pos, Layer layer) {
    static sf::Vector2i dirs[8] = {sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(1, -1), sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, 1), sf::Vector2i(1, 1)};
    int nb=0, id=GetTile(pos, layer);
    for(int i=0 ; i<8 ; i++) {
        if(GetTile(pos+dirs[i], layer) == id) {
            nb++;
        }
    }
    return nb;
}

int Map::GetNbDirNeighboursCode(sf::Vector2i pos, Layer layer, bool diagonal) {
    int nb=0, id=_tileTypes[GetTile(pos, layer)];
    if(!diagonal) {
        static sf::Vector2i dirs[4] = {sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0)};
        for(int i=0 ; i<4 ; i++) {
            if(_tileTypes[GetTile(pos+dirs[i], layer)] == id) {
                nb+=pow(2, i);
            }
        }
    } else {
        static sf::Vector2i dirs[4] = {sf::Vector2i(1, -1), sf::Vector2i(1, 1), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1)};
        for(int i=0 ; i<4 ; i++) {
            if(_tileTypes[GetTile(pos+dirs[i], layer)] == id) {
                nb+=pow(2, i);
            }
        }
    }
    return nb;
}

void Map::SetTile(sf::Vector2i pos, int id, Layer layer) {
    if(!IsOnMap(pos)) {
        return;
    }
    _tiles[layer][pos.x][pos.y] = id;
}

bool Map::IsLocalCollided(sf::Vector2f pos, TileType type) {
    if(type == WALL || type == VOID) {
        return true;
    } else if(type == PLATFORM) {
        if(sf::FloatRect(0, 0, 16, 3).contains(pos)) {
            return true;
        }
    }
    return false;
}

bool Map::IsCollided(sf::FloatRect rect, TileType type) {
    std::vector<sf::Vector2f> corners = MathHelper::Rect2Corners(rect);
    for(float i=corners[0].x ; i<corners[1].x ; i+=2) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(i, corners[0].y)/16.f), FRONT)] == type) {
            return true;
        }
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(i, corners[2].y)/16.f), FRONT)] == type) {
            return true;
        }
    }
    for(float i=corners[0].y ; i<corners[2].y ; i+=2) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[0].x, i)/16.f), FRONT)] == type) {
            return true;
        }
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[2].x, i)/16.f), FRONT)] == type) {
            return true;
        }
    }
    if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(corners[2])/16.f), FRONT)] == type) {
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

bool Map::IsOnTileType(sf::FloatRect rect, TileType type) {
    for(float i=0 ; i<rect.width ; i+=8) {
        if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(rect.left+i, rect.top+rect.height+1)/16.f), FRONT)] == type) {
            return true;
        }
    }
    if(_tileTypes[GetTile(sf::Vector2i(sf::Vector2f(rect.left+rect.width, rect.top+rect.height+1)/16.f), FRONT)] == type) {
        return true;
    }
    return false;
}

bool Map::IsOnTileType(MovingSprite& sprite, sf::Vector2f pos, TileType type) {
    sf::FloatRect rect = sprite.GetGlobalHitbox();
    return IsOnTileType(sf::FloatRect(pos.x, pos.y, rect.width, rect.height), type);
}

bool Map::IsOnTileType(MovingSprite& sprite, TileType type) {
    return IsOnTileType(sprite, sf::Vector2f(sprite.GetGlobalHitbox().left, sprite.GetGlobalHitbox().top), type);
}
