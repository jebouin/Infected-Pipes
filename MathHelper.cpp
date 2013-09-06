#include "MathHelper.h"

float MathHelper::ABS(float n) {
    return (n<0 ? -n : n);
}

sf::Vector2f MathHelper::ABS(sf::Vector2f v) {
    return sf::Vector2f(ABS(v.x), ABS(v.y));
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

sf::FloatRect MathHelper::View2Rect(sf::View& view) {
    return sf::FloatRect(sf::Vector2f(view.getCenter()-view.getSize()/2.f), sf::Vector2f(view.getSize()));
}

sf::Vector2f MathHelper::GetCenter(sf::FloatRect rect) {
    return sf::Vector2f(rect.left, rect.top) + sf::Vector2f(rect.width, rect.height)/2.f;
}

float MathHelper::GetVecLength(sf::Vector2f vec) {
    return sqrt(vec.x*vec.x + vec.y*vec.y);
}

sf::Vector2f MathHelper::Normalize(sf::Vector2f vec) {
    return vec/GetVecLength(vec);
}
