#include "Grass.h"
#include "IP.h"
#include "Level.h"
#include "Map.h"
#include "Renderer.h"
#include "MathHelper.h"

Grass::Grass(IP& ip, Level& level) {
    _grass.setPrimitiveType(sf::Lines);
    Map& map(level.GetMap());
    for(int i=0 ; i<map.GetSize().x ; i++) {
        for(int j=0 ; j<map.GetSize().y ; j++) {
            if(map.GetTile(sf::Vector2i(i, j)) == 0 && map.GetTile(sf::Vector2i(i, j+1)) == 1) {
                for(int p=0 ; p<32 ; p++) {
                    sf::Color c(101, MathHelper::RandFloat(80, 150), MathHelper::RandFloat(59, 80));
                    sf::Vector2f pos(i*16+p/2.f, j*16+16 + MathHelper::RandFloat(0, 2));
                    _blades.push_back(GrassBlade{pos, MathHelper::RandInt(2, 8), -90});
                    _grass.append(sf::Vertex(pos, c));
                    _grass.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), c));
                }
            }
        }
    }
    _windNoise = MathHelper::GetPerlin(1024);
}

Grass::~Grass() {

}

void Grass::Update(IP& ip) {
    int x = (int)(_timer.getElapsedTime().asMilliseconds()*128/1000.f);
    for(int i=0 ; i<_blades.size() ; i++) {
        int perlinId = (i+x)%_windNoise.size();
        _blades[i].angle = (_windNoise[perlinId] - 0.7)*140.f - 90.f;
        sf::Vertex& v(_grass[i*2+1]);
        v.position = MathHelper::Ang2Vec(MathHelper::Deg2Rad(_blades[i].angle))*_blades[i].length + _grass[i*2].position;
    }
}

void Grass::Draw(IP& ip) {
    ip._renderer->Draw(_grass);
}
