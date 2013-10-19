#ifndef WATERFIELD_H_INCLUDED
#define WATERFIELD_H_INCLUDED

#include <iostream>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class IP;
class ParticleManager;

struct Spring {
    float _nLength;
    float _length;
    float _velocity;
};

class WaterField {
    public:
    WaterField(sf::FloatRect rect, float resolution, bool surface);
    ~WaterField();
    void Update(float elapsedTime);
    void Draw(IP& ip);
    void Splash(sf::Vector2f pos, float force, ParticleManager& pManager, IP& ip);
    sf::FloatRect GetRect();

    private:
    sf::VertexArray _vertexes;
    sf::FloatRect _rect;
    vector<Spring> _springs;
    int _nbPoints;
    float _resolution;
    bool _surface;
};

#endif // WATERFIELD_H_INCLUDED
