#include "MathHelper.h"

float MathHelper::ABS(float n) {
    return (n<0 ? -n : n);
}

float MathHelper::SGN(float n) {
    return (n==0 ? 0 : n/ABS(n));
}

int MathHelper::RandInt(int min, int max) {
    return rand()%(max-min) + min;
}

float MathHelper::RandFloat(float min, float max) {
    return float(rand())/float(RAND_MAX)*(max-min) + min;
}

vector<sf::Vector2f> MathHelper::Rect2Corners(sf::FloatRect rect) {
    static sf::Vector2i CPOS[4] = {sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, 1)};
    vector<sf::Vector2f> corners;
    for(int i=0 ; i<4 ; i++) {
        corners.push_back(sf::Vector2f(rect.left, rect.top) + sf::Vector2f(rect.width*CPOS[i].x, rect.height*CPOS[i].y));
    }
    return corners;
}
