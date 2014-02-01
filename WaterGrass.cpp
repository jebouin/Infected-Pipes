#include "WaterGrass.h"
#include "IP.h"
#include "Map.h"
#include "Renderer.h"
#include "MathHelper.h"

WaterGrass::WaterGrass(IP& ip, Map& map) {
    _grass.setPrimitiveType(sf::Lines);
    sf::Vector2i msize(map.GetSize());
    vector<vector<bool> > tilesToGrass(msize.x, vector<bool>(msize.y, false));
    for(int i=0 ; i<msize.x ; i++) {
        for(int j=0 ; j<msize.y ; j++) {
            if(map.GetTile(sf::Vector2i(i, j), Map::FRONT) == 0) {
                //right tiles, let's see if it's a border
                bool border = false;
                for(int d=0 ; d<4 ; d++) {
                    if(map.GetTile(sf::Vector2i(i, j) + DIRS[d], Map::FRONT) == 15) {
                        border = true;
                    }
                }
                if(border) {
                    tilesToGrass[i][j] = true;
                }
            }
        }
    }

    for(int i=0 ; i<msize.x ; i++) {
        for(int j=0 ; j<msize.y ; j++) {
            if(tilesToGrass[i][j]) {
                PutGrassHere(map, sf::Vector2i(i, j));
            }
        }
    }
    _flowNoise = MathHelper::GetPerlin(1024);
}

void WaterGrass::PutGrassHere(Map& map, sf::Vector2i pos) {
    bool w[4]{false};
    for(int i=0 ; i<4 ; i++) {
        if(map.GetTile(pos+DIRS[i], Map::FRONT) == 15) {
            w[i] = true;
        }
    }
    static const sf::Color cs[3] = {sf::Color(19, 38, 40), sf::Color(23, 56, 46), sf::Color(44, 68, 61)};
    static const int maxOff(3);
    static const int minL(2);
    static const int maxL(6);
    sf::Vector2f cpos(0, 0);
    if(w[0]) {
        for(int i=0 ; i<32 ; i++) {
            sf::Color c = cs[rand()%3];
            cpos = sf::Vector2f(pos.x*16-MathHelper::RandInt(0, maxOff), pos.y*16+i/2.f);
            _blades.push_back(WaterGrassBlade{cpos, MathHelper::RandInt(minL, maxL), 0, 0});
            _grass.append(sf::Vertex(cpos, c));
            _grass.append(sf::Vertex(cpos, c));
        }
    }
    if(w[1]) {
        for(int i=0 ; i<32 ; i++) {
            sf::Color c = cs[rand()%3];
            cpos = sf::Vector2f(pos.x*16+16+MathHelper::RandInt(0, maxOff), pos.y*16+i/2.f);
            _blades.push_back(WaterGrassBlade{cpos, MathHelper::RandInt(minL, maxL), 180, 180});
            _grass.append(sf::Vertex(cpos, c));
            _grass.append(sf::Vertex(cpos, c));
        }
    }
    if(w[2]) {
        for(int i=0 ; i<32 ; i++) {
            sf::Color c = cs[rand()%3];
            cpos = sf::Vector2f(pos.x*16+i/2.f, pos.y*16+16+MathHelper::RandInt(0, maxOff));
            _blades.push_back(WaterGrassBlade{cpos, MathHelper::RandInt(minL, maxL), -90, -90});
            _grass.append(sf::Vertex(cpos, c));
            _grass.append(sf::Vertex(cpos, c));
        }
    }
    if(w[3]) {
        for(int i=0 ; i<32 ; i++) {
            sf::Color c = cs[rand()%3];
            cpos = sf::Vector2f(pos.x*16+i/2.f, pos.y*16-MathHelper::RandInt(0, maxOff));
            _blades.push_back(WaterGrassBlade{cpos, MathHelper::RandInt(minL, maxL), 90, 90});
            _grass.append(sf::Vertex(cpos, c));
            _grass.append(sf::Vertex(cpos, c));
        }
    }
}

WaterGrass::~WaterGrass() {

}

void WaterGrass::Update(IP& ip) {
    int x = (int)(_timer.getElapsedTime().asMilliseconds()*128/2000.f);
    for(int i=0 ; i<_blades.size() ; i++) {
        int perlinId = (i+x)%_flowNoise.size();
        _blades[i].angle = (_flowNoise[perlinId] - 0.5)*80-40 + _blades[i].baseAngle;
        sf::Vertex& v(_grass[i*2+1]);
        v.position = MathHelper::Ang2Vec(MathHelper::Deg2Rad(_blades[i].angle))*_blades[i].length + _grass[i*2].position;
    }
}

void WaterGrass::Draw(sf::RenderTexture& rt) {
    rt.draw(_grass);
}
