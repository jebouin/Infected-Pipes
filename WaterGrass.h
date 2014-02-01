#ifndef WATERGRASS_H_INCLUDED
#define WATERGRASS_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Grass.h"

using namespace std;

class IP;
class Map;

struct WaterGrassBlade {
    sf::Vector2f pos;
    float length;
    float angle;
    float baseAngle;
};

static const sf::Vector2i DIRS[4] = {sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1)};

class WaterGrass {
    public:
    WaterGrass(IP& ip, Map& map);
    void PutGrassHere(Map& map, sf::Vector2i pos);
    ~WaterGrass();
    void Update(IP& ip);
    void Draw(sf::RenderTexture& rt);

    private:
    sf::Clock _timer;
    sf::VertexArray _grass;
    std::vector<WaterGrassBlade> _blades;
    std::vector<float> _flowNoise;
};

#endif // WATERGRASS_H_INCLUDED
