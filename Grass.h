#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class Map;

struct GrassBlade {
    sf::Vector2f pos;
    float length;
    float angle;
};

class Grass {
    public:
    Grass(IP& ip, Map& map);
    ~Grass();
    void Update(IP& ip);
    void Draw(sf::RenderTexture& rt);

    private:
    sf::Clock _timer;
    sf::VertexArray _grass;
    std::vector<GrassBlade> _blades;
    std::vector<float> _windNoise;
};

#endif // GRASS_H_INCLUDED
