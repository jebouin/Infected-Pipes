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
class MovingSprite;

struct Spring {
    float _nLength;
    float _length;
    float _velocity;
};

class WaterField {
    public:
    WaterField(sf::FloatRect rect, float resolution, bool surface, bool lava, bool limited);
    ~WaterField();
    void Update(IP& ip, float elapsedTime, ParticleManager& pManager);
    void Draw(IP& ip, sf::RenderTexture& rt);
    void Splash(sf::Vector2f pos, float force, ParticleManager& pManager, IP& ip);
    bool IsInWater(MovingSprite& sprite);
    void SetLimited(bool l);
    void SetNormalHeight(float normalheight);
    sf::FloatRect GetRect();
    bool IsSurface();
    bool IsLava();
    bool IsLimited();
    float GetNormalHeight();
    int GetId(float x);
    float GetHeight(float x); //inverted!
    float GetY(float x); //not inverted! REAL POS YEAH! \o/ ...!

    private:
    sf::VertexArray _vertexes;
    sf::FloatRect _rect;
    vector<Spring> _springs;
    int _nbPoints;
    float _resolution;
    bool _surface;
    bool _lava;
    bool _limited;

    sf::Color _topc;
    sf::Color _c;
    sf::Color _downc;

    sf::Clock _particleTimer;

    sf::ConvexShape _shape;
};

#endif // WATERFIELD_H_INCLUDED
