#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class Player;
class Character;
class Level;

class Camera : public sf::View {
public:
    Camera(sf::FloatRect size);
    ~Camera();
    void Update(IP& ip, float eTime, Level& level, Character& character);
    void Focus(Character& character);
    void GoLeft();
    void GoRight();
    void GoCenter();

private:
    float _nextRelPosX;
    float _curRelPosX;
    float _prevY;
};

#endif // CAMERA_H_INCLUDED
