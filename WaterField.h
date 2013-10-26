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
    WaterField(sf::FloatRect rect, float resolution, bool surface, bool lava);
    ~WaterField();
    void Update(float elapsedTime);
    void Draw(IP& ip);
    void Splash(sf::Vector2f pos, float force, ParticleManager& pManager, IP& ip);
    sf::FloatRect GetRect();
    bool IsSurface();
    float GetHeight(float x); //inverted!

    private:
    sf::VertexArray _vertexes;
    sf::FloatRect _rect;
    vector<Spring> _springs;
    int _nbPoints;
    float _resolution;
    bool _surface;
    bool _lava;

    sf::Color _topc;
    sf::Color _c;
    sf::Color _downc;
};

#endif // WATERFIELD_H_INCLUDED
