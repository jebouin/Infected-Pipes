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

float MathHelper::Interpolate(float x, float y0, float y1) {
    return x*(y1-y0) + y0;
}

sf::Vector2f MathHelper::Interpolate(float x, sf::Vector2f v0, sf::Vector2f v1) {
    return sf::Vector2f(Interpolate(x, v0.x, v1.x), Interpolate(x, v0.y, v1.y));
}

int MathHelper::RandInt(int min, int max) {
    return rand()%(max-min+1) + min;
}

float MathHelper::RandFloat(float min, float max) {
    return float(rand())/float(RAND_MAX)*(max-min) + min;
}

string MathHelper::NbToStringWithUnit(int nb) {
    static string symb = "kMGT";
    string s;
    int e=-1;
    while(pow(1000, e+2) <= nb) {
        e++;
    }
    nb = nb/pow(1000, e+1);
    ostringstream os;
    os << nb;
    s = os.str();
    if(e >= 0) {
        s += symb[e];
    }
    return s;
}

string MathHelper::IntToString(int nb) {
    ostringstream os;
    os << nb;
    return os.str();
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

float MathHelper::Deg2Rad(float deg) {
    return deg*PI/180.f;
}

float MathHelper::Rad2Deg(float rad) {
    return rad*180.f/PI;
}

sf::Vector2f MathHelper::Ang2Vec(float angle) {
    return sf::Vector2f(cos(angle), sin(angle));
}

float MathHelper::Vec2Ang(sf::Vector2f vec) {
    return atan2(vec.y, vec.x);
}

vector<float> MathHelper::GetNoise(float width) {
    vector<float> noise(width, 0);
    for(int i=0 ; i<width ; i++) {
        noise[i] = MathHelper::RandFloat(0, 1);
    }
    return noise;
}

vector<float> MathHelper::GetInterplatedNoise(float width, int waveLength) {
    vector<float> baseNoise = GetNoise(width/waveLength);
    vector<float> noise(width, 0);
    for(int i=0 ; i<width ; i++) {
        noise[i] = MathHelper::Interpolate(float(i%waveLength)/(float(waveLength)), baseNoise[i/waveLength], baseNoise[(i/waveLength+1)%int(width/waveLength)]);
    }
    return noise;
}

vector<float> MathHelper::GetPerlin(float width) {
    int nbOctaves = 7;
    float p = 1.f;
    float m = 0.5f;
    float totalP = 0.f;
    vector<float> perlin(width, 0);
    for(int o=0 ; o<nbOctaves ; o++) {
        vector<float> curNoise = GetInterplatedNoise(width, pow(2, nbOctaves-1-o));
        for(int i=0 ; i<width ; i++) {
            perlin[i] += curNoise[i]*p;
        }
        totalP += p;
        p *= m;
    }

    for(int i=0 ; i<width ; i++) {
        perlin[i] /= totalP;
    }
    return perlin;
}

HSV MathHelper::RGBToHSV(sf::Color rgb) {
    HSV c;
    float r=rgb.r, g=rgb.g, b=rgb.b;
    r/=255; g/=255, b/=255;
    float maxi = max(max(r, g), b);
    float mini = min(min(r, g), b);
    c.v = maxi;
    float d = maxi-mini;
    c.s = ((maxi == 0) ? 0 : d / maxi);
    if(maxi == mini) {
        c.h = 0;
    } else {
        if(maxi == r)
            c.h = (g - b) / d + (g < b ? 6.f : 0.f);
        else if(maxi == g)
            c.h = (b - r) / d + 2.f;
        else if(maxi == b)
            c.h = (r - g) / d + 4.f;
        c.h /= 6.f;
    }
    c.h *= 100.f;
    c.s *= 100.f;
    c.v *= 100.f;
    return c;
}

sf::Color MathHelper::HSVToRGB(HSV c) {
    float r, g, b;
    c.h /= 100.f;
    c.s /= 100.f;
    c.v /= 100.f;

    int i = floor(c.h * 6);
    float f = c.h * 6.f - i;
    float p = c.v * (1.f - c.s);
    float q = c.v * (1.f - f * c.s);
    float t = c.v * (1.f - (1.f - f) * c.s);

    switch(i % 6) {
        case 0: r = c.v, g = t, b = p; break;
        case 1: r = q, g = c.v, b = p; break;
        case 2: r = p, g = c.v, b = t; break;
        case 3: r = p, g = q, b = c.v; break;
        case 4: r = t, g = p, b = c.v; break;
        case 5: r = c.v, g = p, b = q; break;
    }
    r*=255;
    g*=255;
    b*=255;

    sf::Color rc(r, g, b);
    return rc;
}
