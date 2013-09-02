#ifndef MATHHELPER_H_INCLUDED
#define MATHHELPER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class MathHelper {
    public:
    static float ABS(float n);
    static sf::Vector2f ABS(sf::Vector2f v);
    static float SGN(float n);
    static int RandInt(int min, int max);
    static float RandFloat(float min, float max);
    static vector<sf::Vector2f> Rect2Corners(sf::FloatRect rect);
    static sf::FloatRect View2Rect(sf::View& view);
};

#endif // MATHHELPER_H_INCLUDED
