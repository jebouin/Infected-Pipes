#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Level;

struct GrassBlade {
    sf::Vector2f pos;
    float length;
    float angle;
};

class Grass {
    public:
    Grass(IP& ip, Level& level);
    ~Grass();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    sf::Clock _timer;
    sf::VertexArray _grass;
    vector<GrassBlade> _blades;
    vector<float> _windNoise;
};

#endif // GRASS_H_INCLUDED
