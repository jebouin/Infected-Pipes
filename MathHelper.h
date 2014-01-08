#ifndef MATHHELPER_H_INCLUDED
#define MATHHELPER_H_INCLUDED

#define RIGHT sf::Vector2i(1, 0)
#define LEFT sf::Vector2i(-1, 0)
#define UP sf::Vector2i(0, -1)
#define DOWN sf::Vector2i(0, 1)

#include <cmath>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#define PI 3.14159265358979323846264338327950 //etc

class IP;

struct HSV {
    float h;
    float s;
    float v;
};

class MathHelper {
    public:
    //single numbers manipulation
    template <typename T> static T ABS(T n);
    static sf::Vector2f ABS(sf::Vector2f v);
    template <typename T> static T SGN(T n);
    static float SuperSGN(float n);
    static float Interpolate(float x, float y0, float y1);
    static sf::Vector2f Interpolate(float x, sf::Vector2f v0, sf::Vector2f v1);
    static int RandInt(int min, int max);
    static float RandFloat(float min, float max);
    static std::string NbToStringWithUnit(int nb);
    static std::string IntToString(int nb);

    //rectangles and std::vector manipulation
    static std::vector<sf::Vector2f> Rect2Corners(sf::FloatRect rect);
    static sf::FloatRect View2Rect(const sf::View& view);
    static sf::Vector2f GetCenter(sf::FloatRect rect);
    static float GetVecLength(sf::Vector2f vec);
    static sf::Vector2f Normalize(sf::Vector2f vec);
    static sf::Vector2f GetMousePos(IP& ip);
    static sf::Vector2f Mod(sf::Vector2f vec, float v);
    static sf::Vector2f RandDirVector();

    //trigonometry
    static float Deg2Rad(float deg);
    static float Rad2Deg(float rad);
    static sf::Vector2f Ang2Vec(float angle);
    static float Vec2Ang(sf::Vector2f vec);

    //noises
    static std::vector<float> GetNoise(float width);
    static std::vector<float> GetInterplatedNoise(float width, int waveLength);
    static std::vector<float> GetPerlin(float width);

    //color manipulation
    static HSV RGBToHSV(sf::Color rgb);
    static sf::Color HSVToRGB(HSV hsv);
};

#endif // MATHHELPER_H_INCLUDED
