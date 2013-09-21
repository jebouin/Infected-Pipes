#ifndef MATHHELPER_H_INCLUDED
#define MATHHELPER_H_INCLUDED

#include <iostream>
#include <cmath>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#define PI 3.14159265358979323846264338327950 //etc

using namespace std;

class MathHelper {
    public:
    static float ABS(float n);
    static sf::Vector2f ABS(sf::Vector2f v);
    static float SGN(float n);
    static float Interpolate(float x, float y0, float y1);
    static sf::Vector2f Interpolate(float x, sf::Vector2f v0, sf::Vector2f v1);
    static int RandInt(int min, int max);
    static float RandFloat(float min, float max);
    static string NbToStringWithUnit(int nb);
    static string IntToString(int nb);
    static vector<sf::Vector2f> Rect2Corners(sf::FloatRect rect);
    static sf::FloatRect View2Rect(sf::View& view);
    static sf::Vector2f GetCenter(sf::FloatRect rect);
    static float GetVecLength(sf::Vector2f vec);
    static sf::Vector2f Normalize(sf::Vector2f vec);
    static float Deg2Rad(float deg);
    static float Rad2Deg(float rad);
    static sf::Vector2f Ang2Vec(float angle);
    static float Vec2Ang(sf::Vector2f vec);
    static vector<float> GetNoise(float width);
    static vector<float> GetInterplatedNoise(float width, int waveLength);
    static vector<float> GetPerlin(float width);
};

#endif // MATHHELPER_H_INCLUDED
